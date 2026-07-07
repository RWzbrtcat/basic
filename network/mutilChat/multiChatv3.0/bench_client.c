#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#define PORT "9034"
#define MAX_CONN 5000
#define MSG "你好，这是一条中文测试消息"

static volatile sig_atomic_t running = 1;

static void sig_handler(int sig)
{
	(void)sig;
	running = 0;
	printf("\n收到中断信号，正在优雅退出...\n");
}

static void set_nonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char *argv[])
{
	int total = MAX_CONN;
	int batch = 100;
	int delay_ms = 0;

	if (argc > 1) total = atoi(argv[1]);
	if (argc > 2) batch = atoi(argv[2]);
	if (argc > 3) delay_ms = atoi(argv[3]);

	printf("=== 高并发测试客户端 ===\n");
	printf("目标: %d 连接, 每批 %d 个, 间隔 %d ms\n", total, batch, delay_ms);

	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, sig_handler);

	struct addrinfo hints, *ai;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	int rv;
	if ((rv = getaddrinfo("127.0.0.1", PORT, &hints, &ai)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	int *fds = calloc(total, sizeof(int));
	int connected = 0;
	int failed = 0;

	struct timeval start, end;
	gettimeofday(&start, NULL);

	// 分批建立连接
	for (int b = 0; b < total && running; b += batch)
	{
		int limit = (b + batch < total) ? batch : total - b;
		for (int k = 0; k < limit; k++)
		{
			int idx = b + k;
			fds[idx] = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
			if (fds[idx] < 0) { failed++; continue; }

			if (connect(fds[idx], ai->ai_addr, ai->ai_addrlen) < 0)
			{
				if (errno != EINPROGRESS)
				{
					close(fds[idx]);
					fds[idx] = -1;
					failed++;
					continue;
				}
			}
			set_nonblocking(fds[idx]);
		}

		// 等待这批连接完成（用 epoll 检测可写）
		int epfd = epoll_create1(0);
		struct epoll_event ev, events[batch];

		ev.events = EPOLLOUT;
		for (int k = 0; k < limit; k++)
		{
			int idx = b + k;
			if (fds[idx] < 0) continue;
			ev.data.fd = fds[idx];
			epoll_ctl(epfd, EPOLL_CTL_ADD, fds[idx], &ev);
		}

		int remain = limit;
		while (remain > 0 && running)
		{
			int n = epoll_wait(epfd, events, batch, delay_ms > 0 ? delay_ms : 1000);
			if (n == 0) break;
			for (int i = 0; i < n; i++)
			{
				int fd = events[i].data.fd;
				int err; socklen_t len = sizeof(err);
				getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &len);
				if (err == 0) connected++;
				else          { failed++; close(fd); }
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
				remain--;
			}
		}
		close(epfd);

		if (b % 500 == 0 && b > 0)
			printf("  进度: %d/%d 已连接\n", b, total);
		if (delay_ms > 0 && b + batch < total)
			usleep(delay_ms * 1000);
	}

	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

	printf("\n--- 连接阶段 ---\n");
	printf("成功: %d, 失败: %d, 耗时: %.2f 秒\n", connected, failed, elapsed);

	// 等待服务器稳定
	sleep(1);

	if (!running)
		goto cleanup;

	if (connected == 0)
	{
		printf("没有可用连接，退出\n");
		free(fds);
		freeaddrinfo(ai);
		return 1;
	}

	// 少量客户端发送消息（避免广播风暴）
	printf("\n--- 消息发送阶段 (%d 个客户端发送) ---\n", connected < 20 ? connected : 20);
	int sent_ok = 0, sent_err = 0;
	int senders = connected < 20 ? connected : 20;
	for (int i = 0; i < senders && running; i++)
	{
		if (fds[i] < 0) continue;
		char msg[256];
		int len = snprintf(msg, sizeof(msg), "[客户端 %d] %s %d\n", i, MSG, rand() % 10000);
		if (send(fds[i], msg, len, 0) == len)
			sent_ok++;
		else
			sent_err++;
	}
	printf("发送成功: %d, 发送失败: %d\n", sent_ok, sent_err);

	if (!running)
		goto cleanup;

	// 接收一段时间
	printf("\n--- 接收阶段 (5秒) ---\n");
	int epfd = epoll_create1(0);
	struct epoll_event ev, events[256];

	ev.events = EPOLLIN;
	int active = 0;
	for (int i = 0; i < total; i++)
	{
		if (fds[i] < 0) continue;
		ev.data.fd = fds[i];
		epoll_ctl(epfd, EPOLL_CTL_ADD, fds[i], &ev);
		active++;
	}

	time_t recv_start = time(NULL);
	int total_bytes = 0;
	while (time(NULL) - recv_start < 5 && active > 0 && running)
	{
		int n = epoll_wait(epfd, events, 256, 100);
		if (n <= 0) continue;
		for (int i = 0; i < n; i++)
		{
			char rbuf[4096];
			int r = recv(events[i].data.fd, rbuf, sizeof(rbuf), 0);
			if (r <= 0)
			{
				epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
				close(events[i].data.fd);
				active--;
			}
			else
			{
				total_bytes += r;
			}
		}
	}
	close(epfd);
	printf("收到总字节: %d, 仍活跃: %d 连接\n", total_bytes, active);

	if (!running)
		goto cleanup;

	// 部分客户端发送 quit
	if (!running)
		goto cleanup;
	printf("\n--- 退出阶段: %d 个客户端发送 quit ---\n", connected / 4);
	for (int i = 0; i < connected / 4 && fds[i] >= 0 && running; i++)
	{
		if (fds[i] < 0) continue;
		send(fds[i], "quit\r\n", 6, 0);
	}

	// 等待剩下的连接接收广播
	if (running)
		sleep(3);

cleanup:
	// 发送 quit 到所有活跃连接后关闭
	printf("\n--- 清理剩余连接 ---\n");
	for (int i = 0; i < total; i++)
	{
		if (fds[i] >= 0)
		{
			send(fds[i], "quit\r\n", 6, 0);
			close(fds[i]);
		}
	}
	free(fds);
	freeaddrinfo(ai);

	printf("测试完成\n");
	return 0;
}

#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>


class credit_card{
public:
	// 构造函数
	credit_card(const char *bname, int no): bank_name(bname), bill_day_no(no) {}

	std::string bank_name;
	int bill_day_no;  //记账日

	// 计算信用卡的免息期
	int calc_free_days(boost::gregorian::date consume_day = boost::gregorian::day_clock::local_day()) const
	{
		// 得到记账日
		boost::gregorian::date bill_day(consume_day.year(), consume_day.month(), bill_day_no);

		// 判断消费日是否已经过了记账日
		if (consume_day > bill_day)
		{
			// 过了则是下个月的记账日
			bill_day += boost::gregorian::months(1);
		}
		// 计算免息期
		// 20 为免息还款期限
		return (bill_day - consume_day).days() + 20;
	}
	
	// 支持比较操作
	friend bool operator < (const credit_card& l, const credit_card& r)
	{
		// 比较免息期
		return l.calc_free_days() < r.calc_free_days();
	}

};

int main()
{
	// 创建两个信用卡对象
	credit_card A("A bank", 25);
	credit_card B("B bank", 15);

	// 
	credit_card tmp = std::max(A, B);

	std::cout << "应该使用" << tmp.bank_name << ", 免息日期为: " << tmp.calc_free_days() << std::endl;

	return 0;
}

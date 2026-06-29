# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

This is a learning repository for Linux network programming in C. The `mutilChat/` directory contains a single-file multi-client TCP chat server built on `select()`-based I/O multiplexing. The parent `network/` directory holds sibling examples for address processing, byte ordering, socket basics, and related notes.

## Build

Single-file C programs with no build system. Compile with GCC:

```bash
gcc -o multiChat01 multiChat01.c
```

The `_demo` binaries are pre-compiled outputs committed alongside source.

## Architecture

`multiChat01.c` — A single-threaded, event-driven chat server:

- **Port**: `9034` (hardcoded in `PORT` macro)
- **Address resolution**: `getaddrinfo()` with `AF_UNSPEC`, `SOCK_STREAM`, `AI_PASSIVE` — binds to whatever address family is available (IPv4 or IPv6)
- **I/O multiplexing**: `select()` over a master `fd_set`, tracking the listener socket and all client connections
- **Message routing**: Broadcast model — any data received from one client is relayed to every other connected client
- **Special commands**: Sending `"quit"` closes the client connection and notifies remaining clients with `"socket N out"`
- **Socket options**: `SO_REUSEADDR` to avoid `"address already in use"` on restart
- **File descriptor management**: `fdmax` tracks the highest active fd for `select()` loop efficiency; new connections and closed sockets update the master set

## Repo context

This directory sits under `/home/wb/knowledges/network/`, part of a larger knowledge base organized by topic (`cpp/`, `linux/`, `network/`, `mysql/`, `other/`). The network topic is explored across multiple sibling directories — `socket/` for basic socket primitives, `mutilChat/` for the multiplexed chat server, and standalone `.c` / `.md` files for address processing, byte order, and Nagle's algorithm notes.

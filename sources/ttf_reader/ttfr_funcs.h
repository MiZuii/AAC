#include <ttf_reader.h>
#include <unistd.h>
#include <fcntl.h>

#pragma once

int read_ngoback(int fd, off_t offset, void *buf, size_t nbytes);
int get_format0_table(int fd, off_t offset, char *buf);
int get_format4_table(int fd, off_t offset, char *buf);
int get_format6_table(int fd, off_t offset, char *buf);
int get_format12_table(int fd, off_t offset, char *buf);

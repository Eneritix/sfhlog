/*
	Copyright (c) 2018 Eneritix (Pty) Ltd

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */

#include <sfhlog/sinks/sfhlog_sink_stdout_color.h>

#include <stdio.h>
#include <time.h>
#include <sys/time.h>


#define LOG_COLOR_BROWN "\x1b[33m"
#define LOG_COLOR_WHITE "\x1b[97m"
#define LOG_COLOR_RED "\x1b[31m"
#define LOG_COLOR_GREEN "\x1b[32m"
#define LOG_COLOR_DARK_GRAY "\x1b[90m"
#define LOG_COLOR_RESET "\x1b[0m"



void sfhlog_sink_stdout_color(
		void* context,
		const struct sfhlog_logger* logger,
		enum sfhlog_severity severity,
		const char* func,
		unsigned int line,
		const char* fmt,
		va_list ap)
{

	// Timestamp
	struct timeval curTime;
	gettimeofday(&curTime, NULL);
	int milli = curTime.tv_usec / 1000;

	struct tm* timeinfo;
	timeinfo = localtime(&curTime.tv_sec);

	char tag[64];
	strftime(tag, sizeof(tag), "%Y-%m-%d %H:%M:%S", timeinfo);
	printf(LOG_COLOR_DARK_GRAY "%s.%03d" LOG_COLOR_RESET " ", tag, milli);

	// Severity
	switch (severity) {
		case LOG_SEVERITY_ERROR: printf(LOG_COLOR_RED   "-- ERROR -- " LOG_COLOR_RESET); break;
		case LOG_SEVERITY_WARN: printf(LOG_COLOR_WHITE  "-- WARN  -- " LOG_COLOR_RESET); break;
		case LOG_SEVERITY_INFO: printf(LOG_COLOR_RESET  "-- INFO  -- "); break;
		case LOG_SEVERITY_DEBUG: printf(LOG_COLOR_RESET "-- DEBUG -- "); break;
	}


	printf("%s", LOG_COLOR_BROWN);

	// Path
	const char** path = logger->path;
	while (*path) {
		printf("%s::", *path);
		path++;
	}

	// Function and line
	printf( "%s:%u" LOG_COLOR_RESET ": ", func, line);

	// Message
	vprintf(fmt, ap);
	printf("\n");
}

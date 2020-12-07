/* See LICENSE file for copyright and license details. */
#include "computer_specific.h"

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "N/A";

/* maximum output string length */
#define MAXLEN 2048

#ifdef WORK_COMPUTER
	#define WIRELESS_INTERFACE "wlp59s0"
	#define BATTERY            "BAT0"
#else
	#define WIRELESS_INTERFACE "wlp2s0"
	#define BATTERY            "BAT1"
#endif

#define DATE_FORMAT        "%a %-e %h, %-l:%M:%S %p"

#define TEMP(x) "/sys/class/thermal/thermal_zone" x "/temp"

#define IP_LOC_FILE "/mnt/2AD8624BD86214FB/Users/Steven/ip_location"
#define IP_LOCATION "[ -f " IP_LOC_FILE " ] && cat " IP_LOC_FILE

#define PING_FILE "/mnt/2AD8624BD86214FB/Users/Steven/ping"
#define PING "[ -f " PING_FILE " ] && cat " PING_FILE

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function         format          argument */
#ifndef WORK_COMPUTER
	{ temp,             "| %s°C",       TEMP("0")            },
	{ temp,             " | %s°C",      TEMP("1")            },
#else
	{ temp,             "| %s°C",       TEMP("11")            },
	{ temp,             " | %s°C",      TEMP("12")            },
#endif
	{ ram_free,         " | %s",        NULL                 },
	{ wifi_essid,       " | %s",        WIRELESS_INTERFACE   },
#ifndef WORK_COMPUTER
	{ run_command,      " | %s",        PING                 },
	{ run_command,      " | %s",        IP_LOCATION          },
#endif
	{ battery_perc,     " | %s%%",      BATTERY              },
	{ datetime,         " | %s ",      DATE_FORMAT           },
};

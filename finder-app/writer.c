#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments. Usage: %s <file> <string>", argv[0]);
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    FILE *fp = fopen(writefile, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Error opening file: %s", writefile);
        perror("Error opening file");
        closelog();
        return 1;
    }

    if (fprintf(fp, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error writing to file: %s", writefile);
        perror("Error writing to file");
        fclose(fp);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    fclose(fp);
    closelog();
    return 0;
}
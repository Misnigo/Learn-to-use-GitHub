#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3306
#define USR_NAME "Misnigo"
#define PASSWORD "123456"
#define DEFAULT_DB "TEST_TABLE"

int main() {
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		printf("%s", mysql_error(&mysql));
		return -1;
	}
	if (!mysql_real_connect(&mysql, SERVER_IP, USR_NAME,
				PASSWORD, DEFAULT_DB, 
				SERVER_PORT, NULL, 0)) {
		printf("mysql_real_connect : %s\n", mysql_error(&mysql));
		return -2;
	}
	const char sql[50] = "SELECT * FROM TBL";
	if (mysql_real_query(&mysql, sql, strlen(sql))) {
		printf("mysql_real_query : %s\n", mysql_error(&mysql));
 		return -2;
	}
	MYSQL_RES *res = mysql_store_result(&mysql);
	int rows = mysql_num_rows(res);
	int fields = mysql_num_fields(res);
	printf("rows = %d fields = %d\n", rows, fields);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res))) {
		for (int i = 0; i < fields; ++i) {
			printf("%s\t", row[i]);
		}
	}
	return 0;
}	


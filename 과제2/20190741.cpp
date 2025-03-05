/**************************************************
 * Title: DatabaseSystem - Project 2 Example
 * Summary: blah blah
 *  |Date              |Author             |Version
    |2024-12-31        |JEESOO KIM         |1.0.0
**************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost"; // change if necessary
const char* user = "root";      // change if necessary
const char* pw = "@2997299k";       // change if necessary
const char* db = "project";

#define MAX_LEN 13000

int main(void) {
    MYSQL* connection = NULL;
    MYSQL conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;

    FILE* fp = fopen("CRUD.txt", "r");    // open CRUD file.
    if (fp == NULL) {
        fprintf(stderr, "Input CURD file open error!\n");
        exit(0);
    }

    char line[MAX_LEN];
    if (mysql_init(&conn) == NULL)
        printf("mysql_init() error!");
    // MySQL 서버에 연결합니다.
    connection = mysql_real_connect(&conn, host, user, pw, NULL, 3306, (const char*)NULL, 0);   // the first NULL can be replaced to an existing db instance.
    if (connection == NULL) {
        printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
        return 1;
    }
    else {
        printf("Connection Succeed\n\n");
        // 프로젝트 데이터베이스를 선택합니다.
        if (mysql_select_db(&conn, "project")) {
            printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
            return 1;
        }
        // CRUD.txt 파일에서 읽은 라인들을 실행합니다.
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (!strcmp(line, "$$$\n"))      // read lines from CRUD file, '$$$' separates CREATE / DELETE parts.
                break;
            mysql_query(connection, line);
        }
        // 메인 쿼리 유형 선택 루프
        while (1) {
            int input = 0;
            printf("\n\n---------- SELECT QUERY TYPES ----------\n\n");
            printf("\t1. TYPE 1\n");
            printf("\t2. TYPE 2\n");
            printf("\t3. TYPE 3\n");
            printf("\t4. TYPE 4\n");
            printf("\t5. TYPE 5\n");
            printf("\t6. TYPE 6\n");
            printf("\t7. TYPE 7\n");
            printf("\t0. QUIT\n");
            printf("\n----------------------------------------\n");

            
            printf(">>> Please select a query type number. Input 0 to exit: ");
            scanf("%d", &input);
            // 프로그램 종료
            if (input == 0) break;
            else if (input == 1) { 
                // TYPE 1: 특정 구역에 판매 중인 집의 주소를 찾습니다.
                int state = 0;
                char query1[10000] = { 0, };
                printf(">>> The address of homes for sale in the district Mapo is as follows below: \n");

                snprintf(query1, sizeof(query1), "SELECT address FROM property WHERE address LIKE '%%Mapo-gu%%' AND property_id NOT IN (SELECT property_id FROM sold);");
                state = mysql_query(connection, query1);
                if (state == 0)
                {
                    int flag = 1, count = 1;
                    sql_result = mysql_store_result(connection);
                    printf("\n\n-%s\n", "---Address---");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                    {
                        flag = 0;
                        printf("Address %d: %-100s\n", count++, sql_row[0]);
                    }

                    if (flag) {
                        printf("No homes for sale in the district Mapo.\n");
                    }

                    mysql_free_result(sql_result);
                    printf("\n");
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                }



                while (1) {
                    int subtype = 0;
                    printf("\n\n---------- Subtypes in TYPE 1 ----------\n");
                    printf("\t1. TYPE 1-1.\n");

                    printf(">>> Please select a subquery type number. Input 0 to exit: \n");
                    scanf("%d", &subtype);

                    if (subtype == 0) break;
                    else if (subtype == 1) {
                        // TYPE 1-1 쿼리
                        char query2[10000] = { 0, };
                        printf(">>> The address of homes for sale in the district Mapo with price between ￦1,000,000,000 and ￦1,500,000,000 is as follows below: \n");

                        snprintf(query2, sizeof(query2), "SELECT address FROM property WHERE address LIKE '%%Mapo-gu%%' AND property_id NOT IN (SELECT property_id FROM sold) AND price BETWEEN 1000000000 AND 1500000000;");
                        state = mysql_query(connection, query2);
                        if (state == 0)
                        {
                            int flag = 1, count = 1;
                            sql_result = mysql_store_result(connection);
                            printf("\n\n-%s\n", "---Address---");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                            {
                                flag = 0;
                                printf("Address %d: %-100s\n", count++, sql_row[0]);
                            }

                            if (flag) {
                                printf("No homes for sale in the district Mapo within the specified price range.\n");
                            }

                            mysql_free_result(sql_result);
                            printf("\n");
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }
                    }
                    else {
                        printf(">>> Range Subquery type input is 0 ~ 1. Subypes in TYPE 1 restarts.\n");
                    }
                }
           
            }
            else if (input == 2) {
                // TYPE 2 쿼리
                int state = 0;
                char query1[10000] = { 0, };
                printf(">>> The address of homes for sale in the 8th school district is as follows below: \n");

                snprintf(query1, sizeof(query1), "SELECT address FROM property WHERE school_district = 8 AND property_id NOT IN (SELECT property_id FROM sold);");
                state = mysql_query(connection, query1);
                if (state == 0)
                {
                    int flag = 1, count = 1;
                    sql_result = mysql_store_result(connection);
                    printf("\n\n-%s\n", "---Address---");
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                    {
                        flag = 0;
                        printf("Address %d: %-100s\n", count++, sql_row[0]);
                    }

                    if (flag) {
                        printf("No homes for sale in the 8th school district.\n");
                    }

                    mysql_free_result(sql_result);
                    printf("\n");
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                }

                while (1) {
                    int subtype = 0;
                    printf("\n\n---------- Subtypes in TYPE 2 ----------\n");
                    printf("\t1. TYPE 2-1.\n");

                    printf(">>> Please select a subquery type number. Input 0 to exit: \n");
                    scanf("%d", &subtype);

                    if (subtype == 0) break;
                    else if (subtype == 1) {
                        // TYPE 2-1 쿼리
                        char query2[10000] = { 0, };
                        printf(">>> The address of homes for sale in the 8th school district with 4 or more bedrooms and 2 bathrooms is as follows below: \n");

                        snprintf(query2, sizeof(query2), "SELECT address FROM property WHERE school_district = 8 AND property_id NOT IN (SELECT property_id FROM sold) AND number_of_bedrooms >= 4 AND number_of_bathrooms = 2;");
                        state = mysql_query(connection, query2);
                        if (state == 0)
                        {
                            int flag = 1, count = 1;
                            sql_result = mysql_store_result(connection);
                            printf("\n\n-%s\n", "---Address---");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                            {
                                flag = 0;
                                printf("Address %d: %-100s\n", count++, sql_row[0]);
                            }

                            if (flag) {
                                printf("No homes for sale in the 8th school district with 4 or more bedrooms and 2 bathrooms.\n");
                            }

                            mysql_free_result(sql_result);
                            printf("\n");
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }
                    }
                    else {
                        printf(">>> Range Subquery type input is 0 ~ 1. Subypes in TYPE 2 restarts.\n");
                    }
                }
            }

            else if (input == 3) {
                // TYPE 3 쿼리
                int state = 0;
                char query[1000] = { 0, };
                printf(">>> The name of the agent who has sold the most properties in the year 2022 by total won value is as follows below: \n");

                snprintf(query, sizeof(query),
                    "SELECT a.name "
                    "FROM sold s "
                    "JOIN agent a ON s.agent_id = a.agent_id "
                    "WHERE YEAR(s.sold_date) = 2022 "
                    "GROUP BY a.agent_id, a.name "
                    "ORDER BY SUM(s.sold_price) DESC "
                    "LIMIT 1;");

                state = mysql_query(connection, query);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    int flag = 1;
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        flag = 0;
                        printf("Agent Name: %s\n", sql_row[0]);
                    }

                    if (flag) {
                        printf("No properties sold by any agent in the year 2022.\n");
                    }

                    mysql_free_result(sql_result);
                    printf("\n");
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                }

                while (1) {
                    int subtype = 0;
                    printf("\n\n---------- Subtypes in TYPE 3 ----------\n");
                    printf("\t1. TYPE 3-1.\n");
                    printf("\t2. TYPE 3-2.\n");

                    printf(">>> Please select a subquery type number. Input 0 to exit: \n");
                    scanf("%d", &subtype);

                    if (subtype == 0) break;
                    else if (subtype == 1) {
                        // TYPE 3-1 쿼리
                        int k;
                        printf(">>> Enter the number(k) of top agents to retrieve: \n");
                        scanf("%d", &k);
                        char query3_1[1000] = { 0, };
                        snprintf(query3_1, sizeof(query3_1),
                            "SELECT a.agent_id, a.name, SUM(s.sold_price) as total_sold "
                            "FROM sold s "
                            "JOIN agent a ON s.agent_id = a.agent_id "
                            "WHERE YEAR(s.sold_date) = 2023 "
                            "GROUP BY a.agent_id, a.name "
                            "ORDER BY total_sold DESC "
                            "LIMIT %d;", k);

                        int state = mysql_query(connection, query3_1);
                        if (state == 0) {
                            int flag = 1, rank = 1;
                            sql_result = mysql_store_result(connection);
                            printf("\n\n--- Top %d agents by total won value in 2023 ---\n", k);
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                                flag = 0;
                                printf("Rank %d: Agent ID: %s, Name: %s, Total Sold: %s\n", rank++, sql_row[0], sql_row[1], sql_row[2]);
                            }

                            if (flag) {
                                printf("No agents found for the year 2023.\n");
                            }

                            mysql_free_result(sql_result);
                            printf("\n");
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }
                       
                    }
                    else if (subtype == 2) {
                        // TYPE 3-2 쿼리
                        char count_query[1000] = { 0, };
                        snprintf(count_query, sizeof(count_query),
                            "SELECT FLOOR(COUNT(*) * 0.1) AS limit_value FROM agent;");

                        int state = mysql_query(connection, count_query);
                        if (state == 0) {
                            sql_result = mysql_store_result(connection);
                            sql_row = mysql_fetch_row(sql_result);
                            int limit_value = atoi(sql_row[0]);
                            mysql_free_result(sql_result);

                            char query3_2[10000] = { 0, };
                            snprintf(query3_2, sizeof(query3_2),
                                "SELECT a.agent_id, a.name, COALESCE(SUM(s.sold_price), 0) as total_sold "
                                "FROM agent a "
                                "LEFT JOIN sold s ON a.agent_id = s.agent_id AND YEAR(s.sold_date) = 2021 "
                                "GROUP BY a.agent_id, a.name "
                                "ORDER BY total_sold ASC "
                                "LIMIT %d;", limit_value);

                            state = mysql_query(connection, query3_2);
                            if (state == 0) {
                                int flag = 1;
                                sql_result = mysql_store_result(connection);
                                printf("\n\n--- Bottom 10%% agents by total won value in 2021 ---\n");
                                while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                                    flag = 0;
                                    printf("Agent ID: %s, Name: %s, Total Sold: %s\n", sql_row[0], sql_row[1], sql_row[2]);
                                }

                                if (flag) {
                                    printf("No agents found for the year 2021.\n");
                                }

                                mysql_free_result(sql_result);
                                printf("\n");
                            }
                            else {
                                fprintf(stderr, "%s\n", mysql_error(connection));
                            }
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }

                    }
                }
            }
            else if (input == 4) {
                // TYPE 4 쿼리
                int state = 0;
                char query[10000] = { 0, };

                printf(">>> The average selling price and average market time for each agent in 2022 are as follows below: \n");

                snprintf(query, sizeof(query),
                    "SELECT a.agent_id, a.name, "
                    "IFNULL(AVG(s.sold_price), '-') AS avg_selling_price, "
                    "IFNULL(AVG(DATEDIFF(s.sold_date, p.listing_date)), '-') AS avg_market_time "
                    "FROM agent a "
                    "LEFT JOIN sold s ON a.agent_id = s.agent_id AND YEAR(s.sold_date) = 2022 "
                    "LEFT JOIN property p ON s.property_id = p.property_id "
                    "GROUP BY a.agent_id, a.name;");

                state = mysql_query(connection, query);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    printf("\n\n%-10s %-20s %-20s Won %-20s Days\n", "Agent ID", "Name", "Avg Selling Price", "Avg Market Time");
                    int flag = 1;
                    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        flag = 0;
                        printf("%-10s %-20s %-20s Won %-20s Days\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
                    }

                    if (flag) {
                        printf("No data available for the year 2022.\n");
                    }

                    mysql_free_result(sql_result);
                    printf("\n");
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                }

                while (1) {
                    int subtype = 0;
                    printf("\n\n---------- Subtypes in TYPE 4 ----------\n");
                    printf("\t1. TYPE 4-1\n");
                    printf("\t2. TYPE 4-2\n");

                    printf(">>> Please select a subquery type number. Input 0 to exit: \n");
                    scanf("%d", &subtype);

                    if (subtype == 0) break;
                    else if (subtype == 1) {
                        // TYPE 4-1 쿼리
                        char query4_1[1000] = { 0, };
                        snprintf(query4_1, sizeof(query4_1),
                            "SELECT a.agent_id, a.name, "
                            "IFNULL(MAX(s.sold_price), '-') AS max_selling_price "
                            "FROM agent a "
                            "LEFT JOIN sold s ON a.agent_id = s.agent_id AND YEAR(s.sold_date) = 2023 "
                            "GROUP BY a.agent_id, a.name;");

                        int state = mysql_query(connection, query4_1);
                        if (state == 0) {
                            int flag = 1;
                            sql_result = mysql_store_result(connection);
                            printf("\n\n--- Maximum selling price of properties sold in 2023 for each agent ---\n");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                                flag = 0;
                                printf("Agent ID: %s, Name: %s, Max Selling Price: %s Won\n", sql_row[0], sql_row[1], sql_row[2]);
                            }

                            if (flag) {
                                printf("No agents found for the year 2023.\n");
                            }

                            mysql_free_result(sql_result);
                            printf("\n");
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }
                    }
                    else if (subtype == 2) {
                        // TYPE 4-2 쿼리
                        char query4_2[1000] = { 0, };
                        snprintf(query4_2, sizeof(query4_2),
                            "SELECT a.agent_id, a.name, "
                            "IFNULL(MAX(DATEDIFF(s.sold_date, p.listing_date)), '-') AS longest_market_time "
                            "FROM agent a "
                            "LEFT JOIN sold s ON a.agent_id = s.agent_id "
                            "LEFT JOIN property p ON s.property_id = p.property_id "
                            "GROUP BY a.agent_id, a.name;");

                        int state = mysql_query(connection, query4_2);
                        if (state == 0) {
                            int flag = 1;
                            sql_result = mysql_store_result(connection);
                            printf("\n\n--- Longest time the property was on the market for each agent ---\n");
                            while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                                flag = 0;
                                printf("Agent ID: %s, Name: %s, Longest Market Time: %s Days\n", sql_row[0], sql_row[1], sql_row[2]);
                            }

                            if (flag) {
                                printf("No agents found with market time data.\n");
                            }

                            mysql_free_result(sql_result);
                            printf("\n");
                        }
                        else {
                            fprintf(stderr, "%s\n", mysql_error(connection));
                        }
                    }
                    else {
                        printf(">>> Range Subquery type input is 0 ~ 2. Subtypes in TYPE 4 restarts.\n");
                    }
                }

            }
            else if (input == 5) {
                // TYPE 5 쿼리
                int state = 0;
                char query[10000] = { 0, };
                char room_types[4][20] = { "studio", "one-bedroom", "multi-bedroom", "detached" };
                char room_descriptions[4][100] = { "most expensive studio", "most expensive one-bedroom", "most expensive multi-bedroom apartment", "most expensive detached house" };

                for (int i = 0; i < 4; i++) {
                    snprintf(query, sizeof(query),
                        "SELECT p.photo_type, p.image_url FROM photo p "
                        "JOIN property pr ON p.property_id = pr.property_id "
                        "WHERE pr.property_type = '%s' "
                        "AND pr.price = (SELECT MAX(price) FROM property WHERE property_type = '%s');",
                        room_types[i], room_types[i]);
                    state = mysql_query(connection, query);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);
                        printf("\n>>> The %s photos are as follows below:\n\n", room_descriptions[i]);
                        int flag = 1;
                        while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                            flag = 0;
                            printf("%s: %s\n", sql_row[0], sql_row[1]);
                        }
                        if (flag) {
                            printf("No photos found for the %s.\n", room_descriptions[i]);
                        }
                        mysql_free_result(sql_result);
                    }
                    else {
                        fprintf(stderr, "%s\n", mysql_error(connection));
                    }
                }
            }
            else if (input == 6) {
                int state = 0;
                char property_code[20];
                char buyer_name[50];
                char agent_name[50];
                char seller_name[50];
                char sold_date[20];
                double sold_price;
                int property_id, buyer_id, agent_id, seller_id;

                printf(">>> Record the sale of a property.\n");

                // Get property code
                printf("Enter the property code (property_id): ");
                scanf("%s", property_code);

                // Get sold price
                printf("Enter the sold price: ");
                scanf("%lf", &sold_price);

                // Get buyer name
                printf("Enter the buyer name: ");
                scanf(" %[^\n]", buyer_name);

                // Get agent name
                printf("Enter the agent name: ");
                scanf(" %[^\n]", agent_name);

                // Get seller name
                printf("Enter the seller name: ");
                scanf(" %[^\n]", seller_name);

                // Get sold date
                printf("Enter the sold date (YYYY-MM-DD): ");
                scanf("%s", sold_date);

                // Find property_id
                char query_property[1000];
                snprintf(query_property, sizeof(query_property), "SELECT property_id FROM property WHERE property_id = %s AND property_id NOT IN (SELECT property_id FROM sold);", property_code);
                state = mysql_query(connection, query_property);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        property_id = atoi(sql_row[0]);
                    }
                    else {
                        printf("Invalid property code or the property is already sold.\n");
                        mysql_free_result(sql_result);
                        continue;
                    }
                    mysql_free_result(sql_result);
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    return 1;
                }

                // Find buyer_id
                char query_buyer[1000];
                snprintf(query_buyer, sizeof(query_buyer), "SELECT buyer_id FROM buyer WHERE name = '%s';", buyer_name);
                state = mysql_query(connection, query_buyer);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        buyer_id = atoi(sql_row[0]);
                    }
                    else {
                        printf("Invalid buyer name.\n");
                        mysql_free_result(sql_result);
                        continue;
                    }
                    mysql_free_result(sql_result);
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    return 1;
                }

                // Find agent_id
                char query_agent[1000];
                snprintf(query_agent, sizeof(query_agent), "SELECT agent_id FROM agent WHERE name = '%s';", agent_name);
                state = mysql_query(connection, query_agent);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        agent_id = atoi(sql_row[0]);
                    }
                    else {
                        printf("Invalid agent name.\n");
                        mysql_free_result(sql_result);
                        continue;
                    }
                    mysql_free_result(sql_result);
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    return 1;
                }

                // Find seller_id
                char query_seller[1000];
                snprintf(query_seller, sizeof(query_seller), "SELECT seller_id FROM seller WHERE name = '%s';", seller_name);
                state = mysql_query(connection, query_seller);
                if (state == 0) {
                    sql_result = mysql_store_result(connection);
                    if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                        seller_id = atoi(sql_row[0]);
                    }
                    else {
                        printf("Invalid seller name.\n");
                        mysql_free_result(sql_result);
                        continue;
                    }
                    mysql_free_result(sql_result);
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    return 1;
                }

                // Insert into sold table
                char query_insert[1000];
                snprintf(query_insert, sizeof(query_insert), "INSERT INTO sold (property_id, agent_id, buyer_id, seller_id, sold_price, sold_date) VALUES (%d, %d, %d, %d, %lf, '%s');", property_id, agent_id, buyer_id, seller_id, sold_price, sold_date);
                state = mysql_query(connection, query_insert);
                if (state == 0) {
                    printf("The sale has been successfully recorded.\n");
                }
                else {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                }
            }
            else if (input == 7) {
                int agent_id;
                char name[21]; // Adjusting size to fit VARCHAR(20)
                char contact_info[21]; // Adjusting size to fit VARCHAR(20)
                char query[10000] = { 0 };
                int state = 1;

                printf(">>> Registering a new agent.\n");

                // Prompt user to input a non-duplicate agent_id
                while (1) {
                    printf("Agent ID (number between 10000 and 19999): ");
                    scanf("%d", &agent_id);

                    // Check if agent_id is within the range
                    if (agent_id < 10000 || agent_id > 19999) {
                        printf("Agent ID must be a number between 10000 and 19999. Please re-enter.\n");
                        continue;
                    }

                    // Check if agent_id is a duplicate
                    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM agent WHERE agent_id = %d;", agent_id);
                    state = mysql_query(connection, query);
                    if (state == 0) {
                        sql_result = mysql_store_result(connection);
                        sql_row = mysql_fetch_row(sql_result);
                        if (atoi(sql_row[0]) == 0) {
                            mysql_free_result(sql_result);
                            break; // If no duplicate found, exit loop
                        }
                        else {
                            printf("The entered Agent ID already exists. Please enter a different ID.\n");
                            mysql_free_result(sql_result);
                        }
                    }
                    else {
                        fprintf(stderr, "%s\n", mysql_error(connection));
                        return 1;
                    }
                }

                printf("Name(lower than 20 characters): ");
                scanf("%s", name);
                printf("Contact Info(lower than 20 characters): ");
                scanf("%s", contact_info);

                snprintf(query, sizeof(query),
                    "INSERT INTO agent (agent_id, name, contact_info) VALUES (%d, '%s', '%s');",
                    agent_id, name, contact_info);

                state = mysql_query(connection, query);
                if (state == 0) {
                    printf("New agent successfully registered.\n");
                }
                else {
                    fprintf(stderr, "Error registering new agent: %s\n", mysql_error(connection));
                }
            }
            else {
                printf(">>> Range Subquery type input is 0 ~ 7. Program menu restarts!\n");
            }
        }

        /* 아래의 양식을 참고하여 코드를 작성하였음.
        const char* query = "select * from customer";
        int state = 0;
        state = mysql_query(connection, query);
        if (state == 0) {
            sql_result = mysql_store_result(connection);

            printf("[ SELECT * FROM CUSTOMER ]\n");
            while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
                printf(" %s  %s  %s  %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);

            mysql_free_result(sql_result);
        }
        */
        // comment out if you want to persist example db instance.


        while (fgets(line, sizeof(line), fp) != NULL)
            mysql_query(connection, line);			// these are DELETEs & DROPs.

        mysql_close(connection);

        
    }

    return 0;
}

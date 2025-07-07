#include <iostream>
#include <string>
#include <cstdio>
#include <mysql.h>

int main();

void displayMenu();
int productAvailability(MYSQL *conn);          // query 1
int topSellingItems(MYSQL *conn);              // query 2
int storePerformance(MYSQL *conn);             // query 3
int vendorStatistics(MYSQL *conn);             // query 4
int inventoryReorderAlerts(MYSQL *conn);       // query 5
int customerPurchasePatterns(MYSQL *conn);     // query 6
int FranchiseCorporateComparison(MYSQL *conn); // query 7

int main()
{
  // std::ios::sync_with_stdio(true); // cout과 printf 버퍼 동기화용
  MYSQL *conn;

  const char *server = "localhost";
  const char *user = "root";
  const char *password = "1234";  // 여기에 비밀번호 입력
  const char *database = "store"; // 여기에 데이터베이스 이름 입력

  // MySQL 초기화
  conn = mysql_init(nullptr);
  if (conn == nullptr)
  {
    std::cerr << "mysql_init() failed\n";
    return 1;
  }
  // SSL 연결
  mysql_ssl_mode sslmode = SSL_MODE_DISABLED;
  if (mysql_options(conn, MYSQL_OPT_SSL_MODE, &sslmode))
  {
    std::cerr << "mysql_options() failed: " << mysql_error(conn) << "\n";
    mysql_close(conn);
    return 1;
  }
  // MySQL 서버 연결
  if (mysql_real_connect(conn, server, user, password, database, 0, nullptr, 0) == nullptr)
  {
    /*
    std::cerr << "connection failure: " << mysql_error(conn) << std::endl;
    std::cout << "server: " << server << std::endl;
    std::cout << "user: " << user << std::endl;
    std::cout << "password: " << password << std::endl;
    std::cout << "database: " << database << std::endl;
    */
    int error_num = mysql_errno(conn);
    /*
    if (error_num == 1045)
    {
      std::cout << ">>> password wrong!" << std::endl;
    }
    else if (error_num == 2003)
    {
      std::cout << ">>> MySQL server is off or port is wrong!" << std::endl;
    }
    else if (error_num == 2026)
    {
      std::cout << ">>> SSL connection error!" << std::endl;
    }
    */
    std::cerr << "mysql_real_connect() failed\n";
    mysql_close(conn);
    return 1;
  }

  while (true)
  {
    displayMenu();
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
      if (productAvailability(conn) != 0)
      {
        std::cerr << "productAvailability failed\n";
      }
      break;
    case 2:
      if (topSellingItems(conn) != 0)
      {
        std::cerr << "topSellingItems failed\n";
      }
      break;
    case 3:
      if (storePerformance(conn) != 0)
      {
        std::cerr << "storePerformance failed\n";
      }
      break;
    case 4:
      if (vendorStatistics(conn) != 0)
      {
        std::cerr << "vendorStatistics failed\n";
      }
      break;
    case 5:
      if (inventoryReorderAlerts(conn) != 0)
      {
        std::cerr << "inventoryReorderAlerts failed\n";
      }
      break;
    case 6:
      if (customerPurchasePatterns(conn) != 0)
      {
        std::cerr << "customerPurchasePatterns failed\n";
      }
      break;
    case 7:
      if (FranchiseCorporateComparison(conn) != 0)
      {
        std::cerr << "FranchiseCorporateComparison failed\n";
      }
      break;
    case 0:
      std::cout << "Program terminated.\n";
      // 리소스 해제
      mysql_close(conn);
      return 0;
    default:
      std::cout << "Invalid number.\n";
      break;
    }
  }
  mysql_close(conn);

  return 0;
}

void displayMenu()
{
  printf("\n------------ SELECT QUERY TYPES ------------\n\n");

  printf("\t1. TYPE 1\n");
  printf("\t2. TYPE 2\n");
  printf("\t3. TYPE 3\n");
  printf("\t4. TYPE 4\n");
  printf("\t5. TYPE 5\n");
  printf("\t6. TYPE 6\n");
  printf("\t7. TYPE 7\n");
  printf("\t0. QUIT\n\n");
  printf("Select: ");
}

/* query 1 */
int productAvailability(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  const char *valid_UPC[] = {
      "1000000000001", "1000000000002", "1000000000003", "1000000000004", "1000000000005",
      "1000000000006", "1000000000007", "1000000000008", "1000000000009", "1000000000010",
      "1000000000011", "1000000000012", "1000000000013", "1000000000014", "1000000000015",
      "1000000000016", "1000000000017", "1000000000018", "1000000000019", "1000000000020",
      "1000000000021", "1000000000022", "1000000000023", "1000000000024", "1000000000025",
      "1000000000026", "1000000000027", "1000000000028", "1000000000029", "1000000000030",
      "1000000000031", "1000000000032", "1000000000033", "1000000000034", "1000000000035",
      "1000000000036", "1000000000037", "1000000000038", "1000000000039", "1000000000040",
      "1000000000041", "1000000000042", "1000000000043", "1000000000044", "1000000000045",
      "1000000000046", "1000000000047", "1000000000048", "1000000000049", "1000000000050",
      "1000000000051", "1000000000052", "1000000000053", "1000000000054", "1000000000055",
      "1000000000056", "1000000000057", "1000000000058", "1000000000059", "1000000000060"};
  
  printf("------- TYPE 1 -------\n");
  printf("** Which stores currently carry a certain product (by UPC, name, or brand), and how much inventory do they have? **\n");
  char query [1000];
  while (true)
  {
    printf("valid UPC range: 1000000000001 ~ 1000000000060\n");
    printf("select UPC or select exit to exit this query\n");
    printf("select: ");
    char upc_input[14];
    scanf("%13s", upc_input);
  
    // 입력 버퍼 비우기 (남은 문자들 제거)
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (strncmp(upc_input, "exit", 4) == 0){
      printf("exited query 1\n\n");
      return 0;
    }
    int flag = 0;
    for (int i = 0; i < 60; i++)
    {
      if (strncmp(upc_input, valid_UPC[i], 13) == 0) {
        sprintf(query, 
        "SELECT s.store_ID, s.name AS store_name, p.UPC, p.name AS product_name, p.brand, i.current_quantity "
        "FROM inventory AS i "
        "JOIN store AS s ON i.store_ID = s.store_ID "
        "JOIN product AS p ON i.UPC = p.UPC "
        "WHERE i.UPC = '%s' AND i.current_quantity > 0 "
        "ORDER BY i.current_quantity DESC", 
        upc_input);
        flag = 1;
        break;
      }
    }
    if (flag == 1) break;
    printf("not in valid range\n\n");
  }
  
  if (mysql_query(conn, query))
  {
    std::cerr << "Query 1 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공

}

/* query 2 */
int topSellingItems(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 2 -------\n");
  printf("**  Which products have the highest sales volume in each store over the past month? **\n");

  const char * query = "SELECT s.store_ID, s.name AS store_name, p.name AS product_name, SUM(tp.quantity) AS total_sales FROM sales_transaction st JOIN transaction_product tp ON st.transaction_ID = tp.transaction_ID JOIN product p ON tp.UPC = p.UPC JOIN store s ON st.store_ID = s.store_ID WHERE st.transaction_date BETWEEN '2025-05-01' AND '2025-05-31' GROUP BY s.store_ID, s.name, p.UPC, p.name, p.brand HAVING SUM(tp.quantity) = (SELECT MAX(total_qty) FROM (SELECT SUM(tp2.quantity) AS total_qty FROM sales_transaction st2 JOIN transaction_product tp2 ON st2.transaction_ID = tp2.transaction_ID WHERE st2.store_ID = s.store_ID AND st2.transaction_date BETWEEN '2025-05-01' AND '2025-05-31' GROUP BY tp2.UPC) AS store_totals) ORDER BY s.store_ID;";

  if (mysql_query(conn, query))
  {
    std::cerr << "Query 2 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공
}
/* query 3 */
int storePerformance(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 3 -------\n");
  printf("**  Which store has generated the highest overall revenue this quarter? **\n");

  const char *query = "SELECT s.store_ID, "
                      "s.name AS store_name, "
                      "SUM(tp.quantity * p.price) AS total_revenue "
                      "FROM sales_transaction AS st "
                      "JOIN transaction_product AS tp ON st.transaction_ID = tp.transaction_ID "
                      "JOIN product p ON tp.UPC = p.UPC "
                      "JOIN store s ON st.store_ID = s.store_ID "
                      "WHERE st.transaction_date >= '2025-04-01' AND st.transaction_date <= '2025-06-30' "
                      "GROUP BY s.store_ID "
                      "ORDER BY total_revenue DESC "
                      "LIMIT 1 ";
  if (mysql_query(conn, query))
  {
    std::cerr << "Query 3 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공
}
/* query 4 */
int vendorStatistics(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 4 -------\n");
  printf("** Which vendor supplies the most products across the chain, and how many total units have been sold **\n");

  const char *query = "SELECT v.vendor_ID, v.name AS vendor_name, "
                      "COUNT(DISTINCT p.UPC) AS product_diversity_count, "
                      "SUM(tp.quantity) AS total_sold_quantity "
                      "FROM vendor AS v "
                      "JOIN product AS p ON v.vendor_ID = p.vendor_ID "
                      "LEFT JOIN transaction_product AS tp ON p.UPC = tp.UPC "
                      "GROUP BY v.vendor_ID "
                      "ORDER BY product_diversity_count DESC "
                      "LIMIT 1";

  if (mysql_query(conn, query))
  {
    std::cerr << "Query 4 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공
}
/* query 5 */
int inventoryReorderAlerts(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 5 -------\n");
  printf("**  Which products in each store are below the reorder threshold and need restocking? **\n");

  const char *query = "SELECT s.store_ID, "
                      "s.name AS store_name, "
                      "p.name AS product_name, "
                      "i.current_quantity, "
                      "i.reorder_threshold, "
                      "i.reorder_quantity "
                      "FROM inventory AS i "
                      "JOIN store AS s ON i.store_ID = s.store_ID "
                      "JOIN product AS p ON i.UPC = p.UPC "
                      "WHERE i.current_quantity <= i.reorder_threshold";
  if (mysql_query(conn, query))
  {
    std::cerr << "Query 5 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공
}
/* query 6 */
int customerPurchasePatterns(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 6 -------\n");
  printf("** List the top 3 items that loyalty program customers typically purchase with coffee. **\n");

  const char *query;
  while (1)
  {
    printf("There are 3 products you can check. Select options from 1 to 3 or 0 to exit\n");
    printf("1: Americano Coffee\n"); 
    printf("2: Cafe Latte\n");
    printf("3: Iced Coffee\n");
    printf("0: exit from this query\n\n");
    printf("Select: ");
  
    int option;
    int tmp = scanf("%d", &option);
    if (option == 1) {
      // americano coffee
      printf("Americano Coffee\n");
      query = "SELECT p.UPC, p.name AS product_name, p.brand, COUNT(*) AS purchase_count FROM sales_transaction st1 JOIN transaction_product tp1 ON st1.transaction_ID = tp1.transaction_ID JOIN product p1 ON tp1.UPC = p1.UPC JOIN transaction_product tp2 ON st1.transaction_ID = tp2.transaction_ID JOIN product p ON tp2.UPC = p.UPC WHERE st1.loyalty_ID IS NOT NULL AND p1.name = 'Americano Coffee' AND tp2.UPC != tp1.UPC GROUP BY p.UPC, p.name, p.brand ORDER BY purchase_count DESC LIMIT 3;";
      break;
    }
    else if (option == 2) {
      // cafe latte
      printf("Cafe Latte\n");
      query = "SELECT p.UPC, p.name AS product_name, p.brand, COUNT(*) AS purchase_count FROM sales_transaction st1 JOIN transaction_product tp1 ON st1.transaction_ID = tp1.transaction_ID JOIN product p1 ON tp1.UPC = p1.UPC JOIN transaction_product tp2 ON st1.transaction_ID = tp2.transaction_ID JOIN product p ON tp2.UPC = p.UPC WHERE st1.loyalty_ID IS NOT NULL AND p1.name = 'Cafe Latte' AND tp2.UPC != tp1.UPC GROUP BY p.UPC, p.name, p.brand ORDER BY purchase_count DESC LIMIT 3;";
      break;
    }

    else if (option == 3)
    {
      // iced coffee
      printf("Iced Coffee\n");
      query = "SELECT p.UPC, p.name AS product_name, p.brand, COUNT(*) AS purchase_count FROM sales_transaction st1 JOIN transaction_product tp1 ON st1.transaction_ID = tp1.transaction_ID JOIN product p1 ON tp1.UPC = p1.UPC JOIN transaction_product tp2 ON st1.transaction_ID = tp2.transaction_ID JOIN product p ON tp2.UPC = p.UPC WHERE st1.loyalty_ID IS NOT NULL AND p1.name = 'Iced Coffee' AND tp2.UPC != tp1.UPC GROUP BY p.UPC, p.name, p.brand ORDER BY purchase_count DESC LIMIT 3;";
      break;
    }

    else if (option == 0) {
      printf("exited from this query\n\n");
      return 0;
    }

    else {
      printf("wrong number!!\n\n");
    }
  }
  // const char *query = "(SELECT ownership_type, s.store_ID, s.name AS store_name, COUNT(i.UPC) AS product_count FROM store s LEFT JOIN inventory i ON s.store_ID = i.store_ID WHERE s.ownership_type = 'franchise' GROUP BY s.store_ID, s.name LIMIT 1) UNION ALL (SELECT ownership_type, s.store_ID, s.name AS store_name, COUNT(i.UPC) AS product_count FROM store s LEFT JOIN inventory i ON s.store_ID = i.store_ID WHERE s.ownership_type = 'corporate' GROUP BY s.store_ID, s.name LIMIT 1);";

  if (mysql_query(conn, query))
  {
    std::cerr << "Query 6 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공

}
/* query 7 */
int FranchiseCorporateComparison(MYSQL *conn)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  printf("------- TYPE 7 -------\n");
  printf("**  Among franchise-owned stores, which one offers the widest variety of products, and how does that compare to corporate-owned stores? **\n");

  const char *query = "(SELECT ownership_type, s.store_ID, s.name AS store_name, COUNT(i.UPC) AS product_count FROM store s LEFT JOIN inventory i ON s.store_ID = i.store_ID WHERE s.ownership_type = 'franchise' GROUP BY s.store_ID, s.name LIMIT 1) UNION ALL (SELECT ownership_type, s.store_ID, s.name AS store_name, COUNT(i.UPC) AS product_count FROM store s LEFT JOIN inventory i ON s.store_ID = i.store_ID WHERE s.ownership_type = 'corporate' GROUP BY s.store_ID, s.name LIMIT 1);";

  if (mysql_query(conn, query))
  {
    std::cerr << "Query 7 failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 결과 저장
  res = mysql_store_result(conn);
  if (res == nullptr)
  {
    std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
    return 1;
  }

  // 필드 개수 가져오기
  int num_fields = mysql_num_fields(res);
  MYSQL_FIELD *fields = mysql_fetch_fields(res);

  // 헤더 출력
  for (int i = 0; i < num_fields; i++)
  {
    printf("%-25s", fields[i].name);
  }
  printf("\n");
  // 행 출력
  while ((row = mysql_fetch_row(res)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      printf("%-25s", (row[i] ? row[i] : "NULL"));
    }
    printf("\n");
  }

  mysql_free_result(res);

  return 0; // 성공
}
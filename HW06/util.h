#ifndef _UTIL_H_
#define _UTIL_H_

void mainMenu();
int mainOperation();
void fileOperationMenu();
int fileOperation();
int addNewProduct();
int updateProduct();
int deleteProduct();
int addFeautureToProduct();
int addStockEntry();
int deleteStockEntry();
int updateStockEntry();
int backToMenu();
int queryProduct();
void queryMenu();
int listAllProduct();
int listProductsByFeature();
int exportReport(double product[100][3]);
int brandStockControl();
int queryStockByBranchProduct();
int checkStockStatus();
int myStrcmp(const char* str1, const char* str2);
int listTheStockByBranch();
int listTheStockByBranch();
int listOutOfStockProductsByBranch();



#endif /* _UTIL_H_ */

/******************************************************************************* 
 *      File Name: jony_udf.c                                                
 *         Author: Jony Wang. (c) 2012                              
 *           Mail: wangjianyign@baidu.com                                         
 *   Created Time: 2012/08/30-15:33                                     
 *      Modified Time: 2012/08/30-15:33                                     
 *******************************************************************************/ 

#define  MYSQL_SERVER 
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include "mysql.h" 
#include "mysql_version.h" 
#include "mysql_priv.h" 
#include "sql_cache.h" 

extern "C"{ 
    my_bool qcdump_init(UDF_INIT *initid,UDF_ARGS *args,char *message); 
    char* qcdump(UDF_INIT *initid,UDF_ARGS *args,char *result,unsigned long *length,char *is_null,char *error); 
    void qcdump_deinit(UDF_INIT *initid); 
} 

extern Query_cache query_cache; 


class Qcdump: private Query_cache{ 

    public : HASH *get_queries() { 
                 return &this->queries; 
             } 
}; 

my_bool qcdump_init(UDF_INIT *initid,UDF_ARGS *args,char *message) { 

    if(args->arg_count > 1) { 
        strcpy(message,"qcdump() can accecpt only one arguments or none arguments"); 
        return 1; 
    } 

    if(args->arg_count == 1 && args->arg_type[0] != STRING_RESULT) { 
        strcpy(message,"qcdump() can accecpt only one STRING arguments"); 
        return 1; 
    } 

    initid->ptr =(char*)malloc(512); 
    memset(initid->ptr,'\0',512); 
    initid->const_item = 0; 
    initid->maybe_null = 0; 
    sql_print_information("qcdump_init() inited succeed!"); 
    return 0; 
} 

char* qcdump(UDF_INIT *initid,UDF_ARGS *args,char *result,unsigned long *length,char *is_null,char *error) { 

    THD *thd; 
    TABLE_LIST *tables; 
    char *str="qcdump() succeed!"; 

    strcpy(result,str); 
    *length = strlen(str); 
    Qcdump *qcdump; 
    HASH *queries; 

    qcdump=(Qcdump*)&query_cache; 
    query_cache.lock(); 
    queries = qcdump->get_queries(); 
    sql_print_information("Queries number in query cache is %d",queries->records); 

    Query_cache_block *qcb; 
    Query_cache_query *qcq; 

    for(uint32_t i =0;i<queries->records;i++) { 

        qcb = (Query_cache_block*)hash_element(queries,i); 
        qcq = qcb->query(); 
        sql_print_information("%d:->%s",i+1,(const char*)qcq->query()); 
    } 

    query_cache.unlock(); 
    return result; 
} 

void qcdump_deinit(UDF_INIT *initid) { 
    sql_print_information("qcdump_deinit() called succeed!"); 
    free(initid->ptr); 
} 

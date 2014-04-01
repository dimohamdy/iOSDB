//
//  iOSDB.h
//  iOSDB
//
//  Created by Süleyman Çalık on 12/29/10.
//  Copyright 2010 Süleyman Çalık All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "sqlite3.h"


@interface iOSDB : NSObject 
{
	sqlite3 * database;
	BOOL isDatabaseOpen;
}
@property BOOL isDatabaseOpen;

/*
 
 */
+(void)setupWithFileName:(NSString *)name
               extension:(NSString *)extension
                 version:(NSString *)version;

/**
 Supports simple select queries like:
 SELECT a , b FROM todos WHERE a = 1 AND b = 2
 
 If elements argument is nil or empty array:
 SELECT * FROM todos WHERE a = 1 AND b = 2
 */
+(NSArray *)selectFromTable:(NSString *)table
                   elements:(NSArray *)elements
                       keys:(NSDictionary *)keys;

+(NSArray *)selectFun:(NSString*)fun FromTable:(NSString *)table
             elements:(NSArray *)elements
                 keys:(NSDictionary *)keys;

//yes equal ASC No equal DESC
+(NSArray *)selectFromTable:(NSString *)table
                   elements:(NSArray *)elements like:(NSString*) pattern orderByElements:(NSMutableArray*)elements order:(bool)order;


+(BOOL)create:(NSString*) type withName:(NSString*)name;

+(BOOL)insertToTable:(NSString *)tableName
            elements:(NSDictionary *)elements;



+(void)alterTable:(NSString*)table operator:(NSString*)DropOrAdd COLUMN:(NSString*) column_name datatype:(NSString*)type;

/**
 ALTER TABLE customers
 ADD (contact_name varchar2(50),
 last_contacted date);
 
 alter table TableName
 drop column Column1, Column2
 
 */
//operator is drop or add in implementation will check to use values
+(BOOL)alterTable:(NSString*)table operator:(NSString*)operators Element:(NSDictionary*) elements;



//JOIN
//operatiors in order of value = != > <
//name must equal in 25 tables
/******
 
 SELECT Customers.CustomerName, Orders.OrderID
 FROM Customers
 FULL OUTER JOIN Orders
 ON Customers.CustomerID=Orders.CustomerID
 ORDER BY Customers.CustomerName;
 
 */
+(NSArray *)selectFromTable:(NSString *)table
                   elements:(NSArray *)elements  join:(NSString*)joinType onElementNames:(NSMutableArray*)names
                   withOperator:(NSMutableArray*)operators orderByElementName:(NSString*)name;



/***
 SELECT column_name(s) FROM table1
 UNION
 SELECT column_name(s) FROM table2;
 
 */
+(NSMutableArray*)unionSelectResult:(NSMutableArray*)selectresult;

+(BOOL)updateTable:(NSString *)tableName
    withControlKey:(NSDictionary *)controlKey
       andElements:(NSDictionary *)elements;


+(BOOL)deleteFromTable:(NSString *)table
        withControlKey:(NSString *)key
              andValue:(NSString *)value;

+(void)clearTable:(NSString *)table;

+(void)clearTables:(NSArray *)tables;

+(void)clearAllTables;

@end

-- List the part number, part description, and units on hand of all parts whose number of units on hand is more than average.

SELECT PART_PART_NUMBER, PART_PART_DESCRIPTION, PART_UNITS_ON_HAND
FROM PART

-- Determine the most expensive part in the database. The MAX function should also be used.

SELECT MAX(PART_UNIT_PRICE)
FROM PART
HAVING MAX(PART_UNIT_PRICE) =
	(SELECT MAX (PART_UNIT_PRICE)
	 FROM PART);

-- Use the IN operator to find the customer number, last name and first name for every customer who placed an order on September 5,2018

SELECT o.ORDR_ORDER_NUMBER, o.ORDR_ORDER_DATE, o.ORDR_CUSTOMER_NUMBER, cu.CUST_CUSTOMER_NUMBER, cu.CUST_LAST, cu.CUST_FIRST
FROM ORDERS o, CUSTOMER cu
WHERE ORDR_ORDER_DATE IN
	(SELECT ORDR_ORDER_DATE
	 FROM ORDERS
	 WHERE ORDR_ORDER_DATE= '05-Sep-2018' AND o.ORDR_CUSTOMER_NUMBER = cu.CUST_CUSTOMER_NUMBER);

-- Repeat the exercise from the prior step using the EXISTS operator

SELECT cu.CUST_CUSTOMER_NUMBER, cu.CUST_LAST, cu.CUST_FIRST
FROM CUSTOMER cu
WHERE EXISTS
	(SELECT o.ORDR_CUSTOMER_NUMBER
	 FROM ORDERS o
	 WHERE ORDR_ORDER_DATE= '05-Sep-2018' AND o.ORDR_CUSTOMER_NUMBER = cu.CUST_CUSTOMER_NUMBER);

-- Find the customer number, last name, and first name for every customer who did not place a order on September 5,2018.

SELECT cU.CUST_CUSTOMER_NUMBER, cu.CUST_LAST, cu.CUST_FIRST
FROM CUSTOMER cu
WHERE cu.CUST_CUSTOMER_NUMBER NOT IN
	(SELECT o.ORDR_CUSTOMER_NUMBER
	 FROM ORDERS o
	 WHERE o.ORDR_ORDER_DATE='05-sep-2018')

-- Find the sales rep number, last name, and first name for every sales rep who represents at least one customer with a credit limit of $2000

SELECT sr.SLSR_SALES_REP_NUMBER, sr.SLSR_LAST, sr.SLSR_FIRST, cu.CUST_CREDIT_LIMIT
FROM SALES_REP sr, CUSTOMER cu
WHERE cu.CUST_CREDIT_LIMIT >=
	(SELECT cU.CUST_CREDIT_LIMIT
	 FROM CUSTOMER cu
	 WHERE cU.CUST_CREDIT_LIMIT = '2000' AND cu.CUST_SALES_REP_NUMBER = sr.SLSR_SALES_REP_NUMBER);

-- List the order number and order date for every order that was placed by Mary Nelson and that contains and order line for an iron.

SELECT ol.ORLN_PART_NUMBER, p.PART_PART_DESCRIPTION, o.ORDR_ORDER_DATE, o.ORDR_ORDER_NUMBER, cu.CUST_LAST, cu.CUST_FIRST
FROM ORDER_LINE ol, PART p, ORDERS o, CUSTOMER cu
WHERE cu.CUST_LAST = 'Nelson'
	AND cu.CUST_FIRST = 'MARY'
	 AND ol.ORLN_PART_NUMBER = 'AX12'
	  AND p.PART_PART_DESCRIPTION = 'Iron'

--  List the order number and order date for every order that was placed by Mary Nelson and that does not contain an order line for an iron. Use a SELECT and a sub SELECT instruction set.

 SELECT DISTINCT ol.ORLN_PART_NUMBER, o.ORDR_ORDER_DATE, o.ORDR_ORDER_NUMBER, cu.CUST_LAST, cu.CUST_FIRST
FROM ORDER_LINE ol, ORDERS o, CUSTOMER cu
WHERE o.ORDR_ORDER_NUMBER IN
	(SELECT ORDR_ORDER_NUMBER
	 FROM ORDERS
	 WHERE ORDR_CUSTOMER_NUMBER = '522'
	 AND o.ORDR_ORDR_NUMBER = ol.ORLN_ORDER_NUMBER
	 AND ol.ORLN_PART_NUMBER != 'AX12');

-- List the part number, part description, unit price, and item class for every part that has a unit price greater than the unit price of any part in item class HW. Use the ALL operator in the query

SELECT PART_PART_NUMBER, PART_PART_DESCRIPTION, PART_UNIT_PRICE, PART_ITEM_CLASS
FROM PART
WHERE PART_UNIT_PRICE > ALL
	(SELECT PART_UNIT_PRICE
	 FROM PART
	WHERE PART_ITEM_CLASS = 'HW')

-- Repeat the exercise from the prior step using the ANY operator in the query instead of the ALL operator

SELECT PART_PART_NUMBER, PART_PART_DESCRIPTION, PART_UNIT_PRICE, PART_ITEM_CLASS
FROM PART
WHERE PART_UNIT_PRICE > ANY
	(SELECT PART_UNIT_PRICE
	 FROM PART
	WHERE PART_ITEM_CLASS = 'HW')
 

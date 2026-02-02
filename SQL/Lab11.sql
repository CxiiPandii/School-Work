-- --------------------------------------------------------------
-- Gabryella Orrego
-- CSC239-02
-- Lab #11
-- First script file: Creating Table Structure for Location Table
-- --------------------------------------------------------------
--Drop the tables if it exists:
DROP TABLE LOCATION;
--Build the table:
CREATE TABLE "LOCATION"
("LOCATIONID" VARCHAR2(3,0),
"LOCATION" VARCHAR2(25) CONSTRAINT "L_LOCATION_NAME" NOT
NULL ENABLE,
"STATE" VARCHAR2(2) CONSTRAINT "L_STATE_NAME" NOT
NULL ENABLE,
"ZIPCODE”NUMBER(5,0) 
CONSTRAINT "LOCATIONID_PK" PRIMARY KEY
("LOCATIONID")
USING INDEX ENABLE
);
























-- --------------------------------------------------------------
-- Gabryella Orrego
-- CSC239-02
-- Lab #11
-- Second script file:Insert commands for Location Table
-- --------------------------------------------------------------
--Load the data records:
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE)
VALUES(‘L01’,’White Plains','NY);
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L02’,’Boston','MA’, ‘02190');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L03’,’Pittsburgh','PA’, ‘15219');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L04’,’Edison','NJ’, ‘12345');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(L05,’New York','NY’, ‘10029');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L06’,’San Francisco','CA’, ‘94102');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L07’,’Jersey City','NJ’, ‘67890');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L08’,’Miami','FL’, ‘33018');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE)
VALUES(‘L09’,’Jacksonville','FL’);
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L10’,’Orlando','FL’, ‘32801');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE,ZIPCODE)
VALUES(‘L11’,Los Angeles','CA’, ‘90210');
INSERT INTO LOCATION(LOCATIONID,LOCATION,STATE)
VALUES(‘L12’,’Cambridge','MA’);













-- --------------------------------------------------------------
-- Gabryella Orrego
-- CSC239-02
-- Lab #11
-- Third script file:SQL Commands
-- --------------------------------------------------------------

--Display Table Structure
DESC
FROM LOCATION;

--Display Original Data
SELECT *
FROM LOCATION;

--Update Postal Codes
UPDATE LOCATION
SET ZIPCODE= ‘10601’
WHERE LOCATION=’White Plains’ AND STATE=’NY’;
UPDATE LOCATION
SET ZIPCODE= ‘32099’
WHERE LOCATION=’Jacksonville’ AND STATE=’FL’;
UPDATE LOCATION
SET ZIPCODE= ‘02138’
WHERE LOCATION=’Cambridge’ AND STATE=’MA’;
UPDATE LOCATION
SET ZIPCODE= ‘08818’
WHERE LOCATION=’Edison’ AND STATE=’NJ’;
UPDATE LOCATION
SET ZIPCODE= ‘07097’
WHERE LOCATION=’Jersey City’ AND STATE=’NJ’;

--Display Data
SELECT *
FROM LOCATION;

--Data Displayed Sorted by Zip
SELECT *
FROM LOCATION
ORDER BY ZIPCODE;

--Display Data by State Then Location
SELECT *
FROM LOCATION
ORDER BY STATE, LOCATION;

//Gabryella Orrego
4
5 import java.io.*;
7
8 public class Lab6
9 {
10 public static void main(String [] args) throws IOException
11 {
12 //Variables
13 float examAvg, //exam average
14 exam1,
15 exam2;
16
17 float sum,
18 sum1,
19 sum2,
20 min1,
21 min2,
22 max1,
23 max2;
24
25 float stnDev1,
26 stnDev2;
27
28 float diffrence;
29
30 String name,
31 nameFind,
32 nameDiffrence,
33 minName1,
34 minName2,
35 maxName1,
36 maxName2,
37 str;
38
39 float classAvg1,
40 classAvg2; //class avgs
41
42 String letterGrade1,
43 letterGrade2; // letter grades
44
45 int choice,
46 count;
47
48
49 int nRows; //rows from datafile
50
51 int letGrdCount1, //for Histogram
52 letGrdCount2,
53 letGrdCount3,
54 letGrdCount4,
55 letGrdCount5,
56 letGrdCount6,
57 letGrdCount7,
58 letGrdCount8,
59 letGrdCount9,
60 letGrdCount10;
Page 1
Lab6.java Tuesday, June 21, 2022, 8:51 PM
61
62
63 //inFile-outFile
64
65 Scanner kb= new Scanner(System.in);
66 File myFile= new File("src/Lab6grades");
67 Scanner inFile;
68 PrintWriter outFile = new PrintWriter("src/Lab6 Grade Report.txt");
69
70 //Prompt Menu!!
71 nRows=25;
72 do
73 {
74 inFile=new Scanner(myFile);
75 System.out.println("\n_______________________");
76 System.out.println("_______________________");
77 System.out.println(" Menu");
78 System.out.println("1: Student Averages");
79 System.out.println("2: Class Average");
80 System.out.println("3: Standard Deviation");
81 System.out.println("4: Letter Grades");
82 System.out.println("5: Minimum/Maximum");
83 System.out.println("6: Specific Student");
84 System.out.println("7: Exam 15% Diffrence");
85 System.out.println("8: Histogram");
86 System.out.println("9: End");
87 System.out.println("_______________________");
88 System.out.println("_______________________");
89 choice=kb.nextInt();
90
91 switch(choice)
92 { //Student Averages (Event
Controlled/FOR LOOP)
93 case 1: System.out.println("___________________________________");
94 System.out.println("___________________________________\n");
95 System.out.println("Student Averages:");
96 inFile.nextLine();
97
98 for(count=1; count<=nRows; count++)
99 {
100 str=inFile.nextLine();
101 name=str.substring(0,25).trim();
102 exam1=Float.parseFloat(str.substring(25,35).trim());
103 exam2=Float.parseFloat(str.substring(35).trim());
104 examAvg=(exam1+exam2)/2;
105 System.out.printf("%-25s%10.2f\n",name, examAvg);
106 } //end of while1
107 System.out.println("___________________________________");
108 System.out.println("___________________________________\n");
109 break;
110 //Class Averages(Event
Controlled/While Loop)
111 case 2: System.out.println("_____________________");
112 System.out.println("_____________________\n");
113 System.out.println("Class Average:");
114 System.out.printf("%10s%10s\n","Exam 1", "Exam 2");
115 inFile.nextLine();
Page 2
Lab6.java Tuesday, June 21, 2022, 8:51 PM
116 count=1;
117 sum1=0;
118 sum2=0;
119 while(count<=nRows)
120 {
121 str=inFile.nextLine();
122 name=str.substring(0,25).trim();
123 exam1=Float.parseFloat(str.substring(25,35).trim());
124 exam2=Float.parseFloat(str.substring(35).trim());
125 sum1=sum1+exam1;
126 sum2=sum2+exam2;
127 count++;
128 } //end of while2
129 classAvg1=sum1/nRows;
130 classAvg2=sum2/nRows;
131 System.out.printf("%10.2f%10.2f\n",classAvg1,classAvg2);
132 System.out.println("_____________________");
133 System.out.println("_____________________\n");
134 break;
135 //Standard Deviation (Event
Controlled/While Loop)
136 case 3:System.out.println("_____________________");
137 System.out.println("_____________________\n");
138 System.out.println("Standard Deviation:");
139 System.out.printf("%10s%10s\n","Exam 1", "Exam 2");
140 inFile.nextLine();
141 count=1;
142 sum1=0;
143 sum2=0;
144 while(count<=nRows)
145 {
146 str=inFile.nextLine();
147 name=str.substring(0,25).trim();
148 exam1=Float.parseFloat(str.substring(25,35).trim());
149 exam2=Float.parseFloat(str.substring(35).trim());
150 sum1=sum1+exam1;
151 sum2=sum2+exam2;
152
153 count++;
154 } //end of while3a
155 classAvg1=sum1/nRows;
156 classAvg2=sum2/nRows;
157
158 inFile.close();
159 inFile=new Scanner(myFile);
160 inFile.nextLine();
161 sum1=0;
162 sum2=0;
163 count=1;
164 while(count<=nRows)
165 {
166 str=inFile.nextLine();
167 name=str.substring(0,25).trim();
168 exam1=Float.parseFloat(str.substring(25,35).trim());
169 exam2=Float.parseFloat(str.substring(35).trim());
170 sum1=(float)(sum1+Math.pow((exam1-classAvg1),2));
171 sum2=(float)(sum1+Math.pow((exam2-classAvg2),2));
Page 3
Lab6.java Tuesday, June 21, 2022, 8:51 PM
172 count++;
173 } //end of while3b
174 stnDev1=(float)Math.sqrt(sum1/nRows);
175 stnDev2=(float)Math.sqrt(sum2/nRows);
176
177 System.out.printf("%10.2f%10.2f\n",stnDev1,stnDev2);
178 System.out.println("_____________________");
179 System.out.println("_____________________\n");
180 break;
181 //Letter Grades(Event
Controlled/While Loop)
182 case 4: System.out.println("_________________________________________________");
183 System.out.println("_________________________________________________\n");
184 System.out.println("Letter Grades:");
185 System.out.printf("%-25s%10s%10s\n","Name","Exam 1", "Exam 2");
186 inFile.nextLine();
187 count=1;
188 while(count<=nRows)
189 {
190 str=inFile.nextLine();
191 name=str.substring(0,25).trim();
192 exam1=Float.parseFloat(str.substring(25,35).trim());
193 exam2=Float.parseFloat(str.substring(35).trim());
194
195 letterGrade1=grades(exam1);
196 letterGrade2=grades(exam2);
197
198 System.out.printf("%-25s%10s%10s\n",name,letterGrade1,letterGrade2);
199 count++;
200 } //end of while4
201 System.out.println("_________________________________________________");
202 System.out.println("_________________________________________________\n");
203 break;
204
205 case 5: System.out.println
("______________________________________________________________________________________");
//MIN AND MAX(Event Controlled/While and if loops)
206 System.out.println
("______________________________________________________________________________________\n");
207 inFile.nextLine();
208 count=1;
209 min1=1000;
210 min2=1000;
211 max1=0;
212 max2=0;
213 minName1="";
214 minName2="";
215 maxName1="";
216 maxName2="";
217 while(count<=nRows)
218 {
219 str=inFile.nextLine();
220 name=str.substring(0,25).trim();
221 exam1=Float.parseFloat(str.substring(25,35).trim());
222 exam2=Float.parseFloat(str.substring(35).trim());
223 if(exam1<min1)
224 {
Page 4
Lab6.java Tuesday, June 21, 2022, 8:51 PM
225 min1=exam1;
226 minName1=name;
227 }
228 if(exam2<min2)
229 {
230 min2=exam2;
231 minName2=name;
232 }
233 if(exam1>max1)
234 {
235 max1=exam1;
236 maxName1=name;
237 }
238 if(exam2>max2)
239 {
240 max2=exam2;
241 maxName2=name;
242 }
243
244 count++;
245 } //end of while5
246 System.out.printf("%-15s%25s%10.2f%25s%10.2f
\n","Min:",minName1,min1,minName2,min2);
247 System.out.printf("\n
%-15s%25s%10.2f%25s%10.2f","Max:",maxName1,max1,maxName2,max2);
248 System.out.println
("\n______________________________________________________________________________________");
249 System.out.println
("______________________________________________________________________________________");
250 break;
251 //Student
Search Name (Event controlled Loop/While and If loops)
252 case 6: System.out.println("_______________________________________________");
253 System.out.println("_______________________________________________\n");
254 System.out.println("Enter Student Name:");
255 kb.nextLine();
256 inFile.nextLine();
257 nameFind=kb.nextLine().trim();
258
259 while(inFile.hasNext())
260 {
261 str=inFile.nextLine();
262 name=str.substring(0,25).trim();
263 exam1=Float.parseFloat(str.substring(25,35).trim());
264 exam2=Float.parseFloat(str.substring(35).trim());
265 if(nameFind.equalsIgnoreCase(name))
266 {
267 System.out.printf("%-25s%10s%10s\n","Name","Exam 1", "Exam 2");
268 System.out.printf("%-25s%10.2f%10.2f\n",name,exam1,exam2);
269 }
270 if(nameFind!=name)
271 {
272 System.out.printf("Error:Name not Found");
273 }
274
275
276 } //end of While6
Page 5
Lab6.java Tuesday, June 21, 2022, 8:51 PM
277
278 System.out.println("________________________________________________");
279 System.out.println("________________________________________________\n");
280 break;
281
282
283 case 7:System.out.println("___________________________________"); //15%
diffrence (Event Controlled Loop/While and if loop)
284 System.out.println("___________________________________\n");
285 System.out.println("15%+ Exam Diffrence:");
286 System.out.printf("\n%-15s%20s","Name","Percent Diffrence");
287 inFile.nextLine();
288 nameFind=kb.nextLine().trim();
289
290
291 nameDiffrence="";
292 diffrence=0;
293 count=1;
294 while(count<=nRows)
295 {
296 str=inFile.nextLine();
297 name=str.substring(0,25).trim();
298 exam1=Float.parseFloat(str.substring(25,35).trim());
299 exam2=Float.parseFloat(str.substring(35).trim());
300
301 diffrence=Math.abs(exam1-exam2);
302 if(diffrence>15)
303 {
304 System.out.printf("\n%-25s%10.1f",name,diffrence);
305 }
306
307 count++;
308 } //End of While
7
309 System.out.println("\n____________________________________");
310 System.out.println("____________________________________\n");
311 break;
312 //Histogram
(Event Controlled Loop/while and if loops)
313 case 8: System.out.println("___________________________________");
314 System.out.println("___________________________________\n");
315 System.out.println("Histogram:\n");
316
317 inFile.nextLine();
318
319 letGrdCount1=0;
320 letGrdCount2=0;
321 letGrdCount3=0;
322 letGrdCount4=0;
323 letGrdCount5=0;
324
325 letGrdCount6=0;
326 letGrdCount7=0;
327 letGrdCount8=0;
328 letGrdCount9=0;
329 letGrdCount10=0;
330
Page 6
Lab6.java Tuesday, June 21, 2022, 8:51 PM
331 while(inFile.hasNext())
332 {
333 str=inFile.nextLine();
334 name=str.substring(0,25).trim();
335 exam1=Float.parseFloat(str.substring(25,35).trim());
336 exam2=Float.parseFloat(str.substring(35).trim());
337 if(exam1>91.0f)
338 {
339 letterGrade1="A";
340
341 }
342 else if(exam1>80.5f)
343 {
344 letterGrade1="B";
345 }
346 else if(exam1>70.0f)
347 {
348 letterGrade1="C";
349 }
350 else if(exam1>59.5f)
351 {
352 letterGrade1="D";
353 }
354 else
355 {
356 letterGrade1="F";
357 }
358 if(exam2>91.0f)
359 {
360 letterGrade2="A";
361
362 }
363 else if(exam1>80.5f)
364 {
365 letterGrade2="B";
366 }
367 else if(exam1>70.0f)
368 {
369 letterGrade2="C";
370 }
371 else if(exam1>59.5f)
372 {
373 letterGrade2="D";
374 }
375 else
376 {
377 letterGrade2="F";
378 }
379
380
381
382 if(letterGrade1=="A")
383 {
384 letGrdCount1++;
385 }
386 else if(letterGrade1=="B")
387 {
Page 7
Lab6.java Tuesday, June 21, 2022, 8:51 PM
388 letGrdCount2++;
389 }
390 else if(letterGrade1=="C")
391 {
392 letGrdCount3++;
393 }
394 else if(letterGrade1=="D")
395 {
396 letGrdCount4++;
397 }
398 else
399 {
400 letGrdCount5++;
401 }
402 if(letterGrade2=="A")
403 {
404 letGrdCount6++;
405 }
406 else if(letterGrade2=="B")
407 {
408 letGrdCount7++;
409 }
410 else if(letterGrade2=="C")
411 {
412 letGrdCount8++;
413 }
414 else if(letterGrade2=="D")
415 {
416 letGrdCount9++;
417 }
418 else
419 {
420 letGrdCount10++;
421 }
422
423
424 } //While 8 end
425 System.out.println("Exam 1");
426 System.out.printf("%-15s%10d\n","A", letGrdCount1);
427 System.out.printf("%-15s%10d\n","B", letGrdCount2);
428 System.out.printf("%-15s%10d\n","C", letGrdCount3);
429 System.out.printf("%-15s%10d\n","D", letGrdCount4);
430 System.out.printf("%-15s%10d\n","F", letGrdCount5);
431
432 System.out.println("Exam 2");
433 System.out.printf("%-15s%10d\n","A", letGrdCount6);
434 System.out.printf("%-15s%10d\n","B", letGrdCount7);
435 System.out.printf("%-15s%10d\n","C", letGrdCount8);
436 System.out.printf("%-15s%10d\n","D", letGrdCount9);
437 System.out.printf("%-15s%10d\n","F", letGrdCount10);
438 break;
439 } //choice switch end
440 inFile.close();
441 }while(choice !=9); //end bracket for 1st do
and while
442
443
Page 8
Lab6.java Tuesday, June 21, 2022, 8:51 PM
444
445
446
447
448
449 } //main end bracket
450
451 public static String grades(float exam1 )
477
478 }//class end bracket
479
480
481 /*
482 Gabryella Orrego
483 Lab 6
484
485
486 _______________________
487 _______________________
488 Menu
489 1: Student Averages
490 2: Class Average
491 3: Standard Deviation
492 4: Letter Grades
493 5: Minimum/Maximum
494 6: Specific Student
495 7: Exam 15% Diffrence
496 8: Histogram
497 9: End
498 _______________________
499 _______________________
500 1
501 ___________________________________
502 ___________________________________
503
504 Student Averages:
505 George Washington 76.35
506 John Adams 62.30
507 Thomas Jefferson 52.00
508 James Madison 85.95
509 James Monroe 65.90
510 John Quincy Adams 76.60
511 Andrew Jackson 77.40
512 Martin Van Buren 94.05
513 William H. Harrison 83.95
514 John Tyler 72.55
515 James K. Polk 91.80
516 Zachary Taylor 66.85
517 Millard Fillmore 71.85
518 Franklin Pierce 63.05
519 James Buchanan 59.35
520 Abraham Lincoln 82.30
521 Andrew Johnson 61.25
522 Ulysses S. Grant 74.95
523 Rutherford B. Hayes 82.75
524 James A. Garfield 76.00
525 Chester A. Arthur 70.35
Page 9
Lab6.java Tuesday, June 21, 2022, 8:51 PM
526 Grover Cleveland 69.55
527 Benjamin Harrison 71.15
528 Grover Cleveland 75.50
529 William McKinley 69.40
530 ___________________________________
531 ___________________________________
532
533
534 _______________________
535 _______________________
536 Menu
537 1: Student Averages
538 2: Class Average
539 3: Standard Deviation
540 4: Letter Grades
541 5: Minimum/Maximum
542 6: Specific Student
543 7: Exam 15% Diffrence
544 8: Histogram
545 9: End
546 _______________________
547 _______________________
548 2
549 _____________________
550 _____________________
551
552 Class Average:
553 Exam 1 Exam 2
554 72.94 73.72
555 _____________________
556 _____________________
557
558
559 _______________________
560 _______________________
561 Menu
562 1: Student Averages
563 2: Class Average
564 3: Standard Deviation
565 4: Letter Grades
566 5: Minimum/Maximum
567 6: Specific Student
568 7: Exam 15% Diffrence
569 8: Histogram
570 9: End
571 _______________________
572 _______________________
573 3
574 _____________________
575 _____________________
576
577 Standard Deviation:
578 Exam 1 Exam 2
579 13.04 13.35
580 _____________________
581 _____________________
582
Page 10
Lab6.java Tuesday, June 21, 2022, 8:51 PM
583
584 _______________________
585 _______________________
586 Menu
587 1: Student Averages
588 2: Class Average
589 3: Standard Deviation
590 4: Letter Grades
591 5: Minimum/Maximum
592 6: Specific Student
593 7: Exam 15% Diffrence
594 8: Histogram
595 9: End
596 _______________________
597 _______________________
598 4
599 _________________________________________________
600 _________________________________________________
601
602 Letter Grades:
603 Name Exam 1 Exam 2
604 George Washington B D
605 John Adams F D
606 Thomas Jefferson F F
607 James Madison C A
608 James Monroe D C
609 John Quincy Adams A F
610 Andrew Jackson C C
611 Martin Van Buren A B
612 William H. Harrison D A
613 John Tyler C D
614 James K. Polk A B
615 Zachary Taylor F C
616 Millard Fillmore C D
617 Franklin Pierce D F
618 James Buchanan D F
619 Abraham Lincoln C A
620 Andrew Johnson D F
621 Ulysses S. Grant D B
622 Rutherford B. Hayes C A
623 James A. Garfield F A
624 Chester A. Arthur D C
625 Grover Cleveland F B
626 Benjamin Harrison B F
627 Grover Cleveland B D
628 William McKinley C F
629 _________________________________________________
630 _________________________________________________
631
632
_______________________
_______________________
Menu
1: Student Averages
2: Class Average
3: Standard Deviation
4: Letter Grades
5: Minimum/Maximum
6: Specific Student
7: Exam 15% Diffrence
8: Histogram
9: End
_______________________
_______________________
5
______________________________________________________________________________________
______________________________________________________________________________________

Min:       Thomas Jefferson       52.80               James Buchanan             50.70

Max:       Martin Van Buren       97.90              William H. Harrison         98.90
______________________________________________________________________________________
______________________________________________________________________________________

_______________________
_______________________
Menu
1: Student Averages
2: Class Average
3: Standard Deviation
4: Letter Grades
5: Minimum/Maximum
6: Specific Student
7: Exam 15% Diffrence
8: Histogram
9: End
_______________________
_______________________
6
_______________________________________________
_______________________________________________

Enter Student Name:
Thomas Jefferson
Name                    Exam 1          Exam 2
Thomas Jefferson         52.80           51.20
________________________________________________
________________________________________________


_______________________
_______________________
Menu
1: Student Averages
2: Class Average
3: Standard Deviation
4: Letter Grades
5: Minimum/Maximum
6: Specific Student
7: Exam 15% Diffrence
8: Histogram
9: End
_______________________
_______________________
7
___________________________________
___________________________________
15%+ Exam Diffrence:

Name               Percent Diffrence
George Washington               27.5
James Madison                   19.7
John Quincy Adams               38.4
William H. Harrison             29.9
Zachary Taylor                  18.7
James Buchanan                  17.3
Abraham Lincoln                 19.0
Rutherford B. Hayes             21.7
James A. Garfield               42.8
Chester A. Arthur               17.7
Grover Cleveland                31.7
Benjamin Harrison               23.9
Grover Cleveland                22.4
William McKinley                19.8
____________________________________
____________________________________


_______________________
_______________________
Menu
1: Student Averages
2: Class Average
3: Standard Deviation
4: Letter Grades
5: Minimum/Maximum
6: Specific Student
7: Exam 15% Diffrence
8: Histogram
9: End
_______________________
_______________________
8
___________________________________
___________________________________

Histogram:

Exam 1
A             3
B             3
C             7
D             7
F             5

Exam 2
A             5
B             6
C             4
D             6
F             4


_______________________
_______________________
Menu
1: Student Averages
2: Class Average
3: Standard Deviation
4: Letter Grades
5: Minimum/Maximum
6: Specific Student
7: Exam 15% Diffrence
8: Histogram
9: End
_______________________
_______________________
 9

*/

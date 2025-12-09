package Bingo;

public class song
{
  public static void reframe(String original, String modified)
  {
    //verse
    int verse = original.length() ‐ modified.length() + 1;                 //this will output verse number (+1 for the original verse with no "clap" modifications)

    //begin verse
    System.out.print("Verse "+verse);
    
    System.out.println("\tThere was a farmer had a dog");
    System.out.println("\tAnd Bingo was his name‐O");

    //writes clap over verse and the B‐I‐N‐G‐O
    for(int i=1;i<=3;i++) //will repeat this line 3 times
    {
    clap(verse);                                                         //will apply the clap method through every new verse

    dashes(original, modified);                                         //will apply dashes through the letters in the "BINGO"

    System.out.println();                                               //start a new line

    }

    System.out.println("\tAnd Bingo was his name‐O\n");


    if(modified.length()==0)                                           //once no more letters it will end verse
    {
        return;
    }
    else                                                              //if letters still need to be modified it will repeat
    {
        reframe( original, modified.substring(1));
    }
  }
public static void clap(int verse)
{
    System.out.print("\t"); //tab
    if(verse==1)
    {
      return;
    }

    System.out.print("("); //( for clap

    for(int clap=1;clap<verse;clap++)
    {
      if(clap==1)
      System.out.print("clap");                                       //first clap
      else
      System.out.print(", clap"); //after first clap
    }
    
    System.out.print(")"); //) for clap
}


public static void dashes(String original, String modified)           //takes input (BINGO) and will put dashes through the word
{
  if(modified.length()!=0 && original.length() != modified.length())
  {
    System.out.print(" ‐ ");
  }

  for(int i=0;i<modified.length();i++)
  {
      if(i!=modified.length()‐1)
      {
        System.out.print(modified.charAt(i)+"‐");
      }
      else
      {
        System.out.print(modified.charAt(i)+"!");
      }
  }

}


//main to test song
public static void main(String[]args)
{
    reframe("BINGO", "BINGO");
}
} //end of song class

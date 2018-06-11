

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!




public class UrlValidatorTest extends TestCase {

  public static void main(String[] args) {

    testIsValid();
  }

   public UrlValidatorTest(String testName) {
      super(testName);
   }



   public void testManualTest()
   {
//You can use this function to implement your manual testing

   }


   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing

   }

   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing

   }
   //You need to create more test cases for your Partitions if you need to

   public static void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
     String []  scheme =  {"http://", "ftp://", "3ht://"};
     String [] authority = {"www.google.com", "go.com", "go.ala"};
     String [] port = {":80", "", ":-2"};
     String [] path = {"/something", "", "///"};
     String [] query = {"", "?action=view","garbage//"};
     Boolean [] mix = {true, true, false};

     for (int sch = 0; sch < 3; sch ++) {
       for (int auth = 0; auth < 3; auth ++) {
         for (int por = 0; por < 3; por ++) {
           for (int pat = 0; pat < 3; pat ++) {
             for (int que = 0; que < 3; que ++) {
               String urlTest = scheme[sch] + authority[auth] + port[por] + path[pat] + query[que];
               Boolean got = urlVal.isValid(urlTest);
               Boolean expected = mix[sch] & mix[auth] & mix[por] & mix[pat] & mix[que];

               if(got != expected) {
                 System.out.println("Expected: " + expected);
                 System.out.println("False parts: ");
                 if (!mix[sch]) System.out.println("Scheme: " + scheme[sch]);
                 if (!mix[auth]) System.out.println("Authority: " + authority[auth]);
                 if (!mix[por]) System.out.println("Port: " + port[por]);
                 if (!mix[pat]) System.out.println("Path: " + path[pat]);
                 if (!mix[que]) System.out.println("Query: " + query[que]);
                 System.out.println();
               }
             }
           }
         }
       }
     }

   }



}

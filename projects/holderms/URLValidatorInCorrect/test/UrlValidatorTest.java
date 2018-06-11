

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


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

   public void testIsValid()
   {
	   //You can use this function for programming based testing
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
               Boolean result = mix[sch] & mix[auth] & mix[por] & mix[pat] & mix[que];
               System.out.println("Result: " + result);
             }
           }
         }
       }
     }

   }



}

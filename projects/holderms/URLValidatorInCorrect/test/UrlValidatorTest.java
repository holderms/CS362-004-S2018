

import java.util.HashMap;

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

	public static void testIsValid()
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		//		String [] scheme =  {"http://", "ftp://", "3ht://"};
		//		String [] authority = {"www.google.com", "go.com", "go.ala"};
		//		String [] port = {":80", "", ":-2"};
		//		String [] path = {"/something", "", "///"};
		//		String [] query = {"", "?action=view","garbage//"};
		//		Boolean [] mix = {true, true, false};

		ResultPair[] scheme = {new ResultPair("http://", true), new ResultPair("ftp://", true), new ResultPair("3ht://", false)};
		ResultPair [] authority = {new ResultPair("www.google.com", true), new ResultPair("go.com", true), new ResultPair("go.ala", false)};
		ResultPair [] port = {new ResultPair(":80", true), new ResultPair("", true), new ResultPair(":-2", false)};
		ResultPair [] path = {new ResultPair("/something", true), new ResultPair("", true), new ResultPair("///", false)};
		ResultPair [] query = {new ResultPair("", true), new ResultPair("?action=view", true), new ResultPair("#//garbage//", false)};
		
		for (int sch = 0; sch < 3; sch ++) {
			System.out.println("Testing scheme: " + scheme[sch].item);
			for (int auth = 0; auth < 3; auth ++) {

				for (int por = 0; por < 3; por ++) {

					for (int pat = 0; pat < 3; pat ++) {

						for (int que = 0; que < 3; que ++) {

							String urlTest = scheme[sch].item + authority[auth].item  + port[por].item  + path[pat].item  + query[que].item ;
							boolean got = urlVal.isValid(urlTest);
							boolean expected = scheme[sch].valid & authority[auth].valid  & port[por].valid  & path[pat].valid  & query[que].valid;
							//assertTrue(got == expected); // crashes
							if(got != expected) {
								System.out.println("Expected: " + expected + " Got: " + got);
								System.out.println("URL " + urlTest);
								if (expected == false) {
									System.out.println("False true");

									
									System.out.println("False parts: ");
									if (!scheme[sch].valid) System.out.println("Scheme: " + scheme[sch].item);
									if (!authority[auth].valid) {
										System.out.println("Authority: " + authority[auth].item);
										//									authorityFailureWhenFalse[auth] += 1;
									}
									if (!port[por].valid) System.out.println("Port: " + port[por].item);
									if (!path[pat].valid) System.out.println("Path: " + path[pat].item);
									if (!query[que].valid) System.out.println("Query: " + query[que].item);
									System.out.println();
								} else if (expected == true) {
									System.out.println("\t\tFALSE FAILURE");

								}
							}
						}
					}
				}
			}

		}
	}

	public static void main(String[] args) {

		testIsValid();
	}

}

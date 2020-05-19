# email_extractor
This is an email extractor which takes any .txt file, searches and finds all the emails.
It has the following features:
  1. it accepts user input files to read and write, if there is not specified file names, it will use default;
  2. if the input and the output file has the same name, it will overwrite the input file (replace the old with new info);
  3. the output file will be a list of emails separated with semicolon(;) and a space (except afte the last email);
  4. if no email was extracted from the input file, it will not open the output file;
  5. it is not using regex when parsing the raw text, the pattern for matching the email addresses is provided in the end of this readme, note that '.@+' is not a valid form for email address in our case, but '_@+' is a valid case. 
                
                
                [(validChars)(validchar except .)@(validChar except .)(validChars)]

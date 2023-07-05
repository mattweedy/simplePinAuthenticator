# simplePinAuthenticator

a program to authenticate an encrypted password PIN. the user can choose to either:
1. encrypt any 4 digit code
2. encrypt the code entered and verify if it matches the (hardcoded) authorised code (4523)
3. decrypt the user-inputted code
4. display the amount of times the code was entered i) correctly ii) incorrectly || (if it matches authorised code)
5. exit the program

the program uses separate functions with pass by reference for each step, 
and certain options should not be allowed to run if the user has not entered a code yet 

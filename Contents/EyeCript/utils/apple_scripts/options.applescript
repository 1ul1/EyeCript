set optionList to {"Encrypt", "Decrypt", "View Encrypted"}

set action2 to choose from list optionList with prompt "What do you want to do?"

delay 0.1

if action2 is false then
	--
else
	set action2 to item 1 of action2

	if action2 is "Encrypt" then 
		do shell script "./EyeCript/build/EC.out enc"
	else if action2 is "Decrypt" then 
		do shell script "./EyeCript/build/EC.out dec"
	else if action2 is "View Encrypted" then 
		do shell script "./EyeCript/build/EC.out view"
	end if
end if
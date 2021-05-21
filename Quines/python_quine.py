#!/usr/bin/python3

# Author: Gautham R. Shenoy (C) 2021.
#
# This is a program whose output is its own code. Such programs are
# called Quines.
#
# The idea is to embed the code of the program inside a string and
# then print it.  But there is one small complication - the string of
# the code should also contain the string of code which should also
# contain a string of code ... ad infinitum.
#
# To get around this, we use a proxy inside the string of the code
# which will indicate where the string should be re-inserted.  Here,
# we use two consecutive dollars in the code_string as that proxy.

code_string="#!/usr/bin/python3\n\n# Author: Gautham R. Shenoy (C) 2021.\n#\n# This is a program whose output is its own code. Such programs are\n# called Quines.\n#\n# The idea is to embed the code of the program inside a string and\n# then print it.  But there is one small complication - the string of\n# the code should also contain the string of code which should also\n# contain a string of code ... ad infinitum.\n#\n# To get around this, we use a proxy inside the string of the code\n# which will indicate where the string should be re-inserted.  Here,\n# we use two consecutive dollars in the code_string as that proxy.\n\ncode_string=$$\n\n# We create a list of strings without the dollar. 36 is the ascii code\n# for dollar. We use the ascii code trick here so that we dont have to\n# refer to dollar again.  They are to be printed as it is, but with\n# the code_string inserted in between.\n\ndollar_split=code_string.split(chr(36) + chr(36))\n\n# Now the literal_string is a variant of code string that would be\n# inserted in place of the two dollars. However, because the\n# code_string contains newline characters which would be interpreted\n# by the print statement, we replace that with a backslash (ascii code\n# 92) followed by an n (ascii code 110). This way it won't be\n# interpreted as a newline while printing the literal string.\n\nliteral_string=code_string.replace(chr(10), chr(92) + chr(110))\n\n# So the output will be first part before the two dollars, double\n# quote (ascii 34) followed by literal string which is a printable\n# version of our code string followed by another double quote (to\n# close the string) followed by the portion of the code_string\n# following the two dollars\n\noutput=dollar_split[0] + chr(34) + literal_string + chr(34) + dollar_split[1]\nprint(output)"

# We create a list of strings without the dollar. 36 is the ascii code
# for dollar. We use the ascii code trick here so that we dont have to
# refer to dollar again.  They are to be printed as it is, but with
# the code_string inserted in between.

dollar_split=code_string.split(chr(36) + chr(36))

# Now the literal_string is a variant of code string that would be
# inserted in place of the two dollars. However, because the
# code_string contains newline characters which would be interpreted
# by the print statement, we replace that with a backslash (ascii code
# 92) followed by an n (ascii code 110). This way it won't be
# interpreted as a newline while printing the literal string.

literal_string=code_string.replace(chr(10), chr(92) + chr(110))

# So the output will be first part before the two dollars, double
# quote (ascii 34) followed by literal string which is a printable
# version of our code string followed by another double quote (to
# close the string) followed by the portion of the code_string
# following the two dollars

output=dollar_split[0] + chr(34) + literal_string + chr(34) + dollar_split[1]
print(output)

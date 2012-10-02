#Primitive Compiler written in pure C.

* Lexical analyzer.

* Parser (Parser was developed in C.)

* Hashtable

* Stack


For hashtable I used this hash function:

	unsigned int Hash(char *str){
		unsigned int h;
		unsigned char *p;
		h = 0;
		for (p = str; *p != '\0'; p++) {
			h = MULTIPLIER * h + *p;
		}
		return (h%NHASH);
	}
	

Developed with great help of the "Compilers: Principles, Techniques, & Tools"
![](http://vig-fp.prenhall.com/bigcovers/0321486811.jpg)
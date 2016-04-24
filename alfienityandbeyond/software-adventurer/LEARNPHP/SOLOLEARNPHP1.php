<?php
	// Hypertext Processor: widely used, open source scripting language
	// PHP script can be placed anywhere in HTML document, executed on server and HTML result sent back to browser
	echo "Hello World!";
	
	// HTML markup can be added to text in echo
	// keywords aren't case-sensitive; variables are
	echo "<h1><strong>This is a bold statement.</strong></h1>";
	
	// VARIABLES: $
	// loosely typed language
	$name = "Alfred Lucero";
	echo "$name does not like php<br>";
	# Scopes: global keyword is used to access a global variable from within a function
	$x = 7;
	$y = 10;
	function practiceSum() {
		global $x, $y;
		$y = $x + $y;
	}
	
	practiceSum();
	echo "Alfred's birthday number is $y<br>";
	# All global variables are stored in an array $GLOBALS[index]
	# can say $GLOBALS['y'] within practiceSum function
	
	# static keyword: each time the function is called, the variable will still have information from last time it was called

	// echo has no return value while print has a return value of 1 to be used in expressions
	// echo can take multiple parameters/faster, print can take one argument
	print "I am using print now<br>";
	
	// Data Types: String, Integer, Float, Boolean, Array, Object, NULL, Resource
	$sample = 123;
	var_dump($sample);
	
	// Strings
	echo strlen("Returns length");
	echo str_word_count("Counts words");
	echo strrev("Reverses string");
	echo strpos("Hello world!", "world");
	echo str_replace("world", "Pikachu", "Hello world!");
	
	// Constants: identifier for a simple value that cannot be changed during script
	// they are global and can be used across entire script
	define("GREETING", "<br>Here is a constant!<br>");
	echo GREETING;
	
	// Operators
	// Arithmetic: +-*/%**
	// Assignment: =+-*/%
	// Comparison: ==, ===(same type as well), != or <>, !==, <=,>=
	// Increment/Decrement: ++, --
	// Logical: and, or, xor, &&, ||, !
	// String: . (concatenation), .+ (concatenation assignment)
	// Array: + (Union), == (same key value pairs), === (identity), != or <>, !==
	
	
?>
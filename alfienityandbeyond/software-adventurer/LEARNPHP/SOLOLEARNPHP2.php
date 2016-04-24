<?php
	// if Statement
	$t = date("H");
	
	if ($t < "20")
		echo "Have a good day!<br>";
	else 
		echo "Have a good night!<br>";
		
	// switch Statement
	$favcolor = "navy";
	switch ($favcolor) {
		case "navy":
			echo "My favorite color is navy blue!<br>";
			break;
		default:
			echo "That is not my favorite color";
	}
	
	// Loops
	// while, do...while, for, foreach (loops through a block of code for each element in an array)
	$colors = array("red", "green", "blue", "yellow");
	
	foreach($colors as $value) {
		echo "$value <br>";
	}
	
	// Functions
	function familyName($fname = "Derpina") {
		echo "$fname Lucero.<br>";
		return 1;
	}
	$houseNumber = familyName("Alfred");
	echo "House number is $houseNumber<br>";
	
	// Arrays
	// Three types of arrays: indexed (numeric index), associative (named keys), multidimensional (one or more arrays)
	$cars = array("Volvo", "BMW", "Toyota");
	echo "I like " . $cars[0] . ", " . $cars[1] . " and " . $cars[2] . ".";
	echo count($cars);
	
	$age = array("Peter"=>"35", "Ben"=>"37", "Joe"=>"43");
	echo "Peter is " . $age['Peter'] . " years old.";
	foreach($age as $x => $x_value) {
    echo "Key=" . $x . ", Value=" . $x_value;
    echo "<br>";
	# Sorting: sort, rsort || (associative) asort, ksort, arsort, krsort
	
	// Superglobals
	// predefined variables in PHP, always accessible regardless of scope
	// i.e. $GLOBALS
	// $_SERVER: holds info. about headers, paths, and script locations
	// $_REQUEST: collects data after submitting HTML form
	// $_POST: collects data/passes variables
	// $_GET: can collect data sent in URL
?>
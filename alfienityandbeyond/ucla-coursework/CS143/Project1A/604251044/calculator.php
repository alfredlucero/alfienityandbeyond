<html>
<body>

<h1><strong>Calculator</strong></h1>
(Ver 1.0 10/05/2015 by Alfred Lucero)<br>
Type an expression in the following box (e.g., 10.5+20*3/25).

<form action="calculator.php" method="GET">
<input type="text" name="expr" />
<input type="submit" name="calculate" value="Calculate">
</form>


<ul>
  <li>Only numbers and +,-,* and / operators are allowed in the expression.</li>
  <li>The evaluation follows the standard operator precedence.</li>
  <li>The calculator does not support parentheses.</li>
  <li>The calculator handles invalid input "gracefully". It does not output PHP error messages.</li>
</ul>

Here are some(but not limit to reasonable test cases):<br>
<ol>
  <li>A basic arithmetic operation: 3+4*5=23</li>
  <li>An expression with floating point or negative sign: -3.2+2*4-1/3 = 4.46666666667, 3*-2.1*2 = -12.6</li>
  <li>Some typos inside operation (e.g. alphabetic letter): Invalid input expression 2d4+1</li>
</ol>


<?php
   if($_GET["expr"]){
   $expr = $_GET["expr"];
   
   
		// Check for errors in mathematical expression
		if (preg_match("/[^0-9\+\-\*\/.]/i", $expr)){
			echo "<h2>Result</h2>";
			echo "Invalid Expression!";
		} else if (preg_match("/\b\/0\b/", $expr)){
			if (preg_match("/\b\/0.\d+\b/", $expr)) {
				eval("\$ans = $expr ;");
				echo "<h2>Result</h2>";
				echo $expr." = ".$ans;
			} else {
				echo "<h2>Result</h2>";
				echo "Division by zero error!";
			}
		} else if (preg_match("/\b(?:\*\+|\/\+|\/\*|\*\/)\b/", $expr)) {
			echo "<h2>Result</h2>";
			echo "Invalid Expression!";
		} else if (preg_match("/\b(?:\*\*|\/\/|\-\-|\+\+)\b/", $expr)) {
			echo "<h2>Result</h2>";
			echo "Invalid Expression!";
		} else {
			eval("\$ans = $expr ;");
			echo "<h2>Result</h2>";
			echo $expr." = ".$ans;
		}
   }
?>

</body>
</html>

<html>
<body>
	
	<form method="post">
	First Number: <input type="number" name="first_operand"><br>
	Operator (+-/*): <input type="text" name="operator" maxlength="1"><br>
	Second Number: <input type="number" name="second_operand"><br>
	<input type="submit" name="calculate" value="Calculate">
	</form>
	
	Calculate: 
	<?php
		// Must validate form data to protect script from malicious code
		// Can also use $_GET
		// Both GET and POST create an array of key(controls)/values(input) and are superglobals
		// $_GET is an array of variables passed to the current script via the URL parameters
		// $_POST is an array of variables passed to the current script via the HTTP POST method
		// Information sent from a form with GET method is visible to everyone (names/values displayed in URL) and has limits on amount of info. to send
		// Don't use GET for passwords/sensitive information
		// POST: invisible to others and no limits on amount of information to send, not possible to bookmark the page	
		
		if (isset($_POST['calculate'])) {
        # Calculate-button was clicked
		echo $_POST["first_operand"]." ".$_POST["operator"]." ".$_POST["second_operand"]." <br>";
		$result;
			switch($_POST["operator"]) {
				case "+":
					$result = $_POST["first_operand"] + $_POST["second_operand"];
					echo "The sum is $result.<br>";
					break;
				case "-":
					$result = $_POST["first_operand"] - $_POST["second_operand"];
					echo "The difference is $result.<br>";
					break;
				case "/":
					$result = $_POST["first_operand"] / $_POST["second_operand"];
					echo "The quotient is $result.<br>";
					break;
				case "*":
					$result = $_POST["first_operand"] * $_POST["second_operand"];
					echo "The product is $result.<br>";
					break;
				default:
					echo "Invalid input: must be an arithmetic operator (*/+-). <br>";
			}
		// Avoid $_SERVER["PHP_SELF"] Exploits/ Cross-Site Scripting with Javascript
		// Pass it through htmlspecialchars() function to avoid inserted scripts
		// trim() function to strip unnecessary characters (extra space, tab, newline)
		// stripslashes() to remove backslashes
		}
	?>
	
	<?php
		if (isset($_POST['submit'])) {
        # Submit-button was clicked
		// define variables and set to empty values if not set already
		// isset determines if a variable is set and is not NULL
		$name = $sid = $email = $comment = $gender = "";
		$nameErr = $emailErr = $sidErr = $genderErr = "";
		/*
		$name = isset($_POST["name"]) ? $_POST["name"] : " ";
		$sid = isset($_POST["sid"]) ? $_POST["sid"] : " ";
		$email = isset($_POST["email"]) ? $_POST["email"] : " ";
		$comment = isset($_POST["comment"]) ? $_POST["comment"] : " ";
		$gender = isset($_POST["gender"]) ? $_POST["gender"] : " ";
		*/
	
		// Clean and check input for special characters, backslashes and white space
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			if (empty($_POST["name"])) {
				$nameErr = "Name is required";
			} else {
				$name = test_input(isset($_POST["name"]) ? $_POST["name"] : " ");
				// check if name only contains letters and whitespace
				if (!preg_match("/^[a-zA-Z ]*$/",$name)) {
					$nameErr = "Only letters and white space allowed"; 
				}
			}
			$sid = test_input(isset($_POST["sid"]) ? $_POST["sid"] : " ");
			$email = test_input(isset($_POST["email"]) ? $_POST["email"] : " ");
			$comment = test_input(isset($_POST["comment"]) ? $_POST["comment"] : " ");
			$gender = test_input(isset($_POST["gender"]) ? $_POST["gender"] : " ");
		}
		}
		function test_input($data) {
			$data = trim($data);
			$data = stripslashes($data);
			$data = htmlspecialchars($data);
			return $data;
		}
		
		// Check if empty and validate for errors
		// validate name: preg_match() searches for string pattern (!preg_match("/^[a-zA-Z]*$/", $var)
		// validate email: !filter_var($email, FILTER_VALIDATE_EMAIL)
		// validate URL: use !preg_match("/\b(?:(?:https?|ftp):\/\/|www\.)[-a-z0-9+&@#\/%?=~_|!:,.;]*[-a-z0-9+&@#\/%=~_|]/i",$website)
		/*
			if ($_SERVER["REQUEST_METHOD"] == "POST") {
				if (empty($_POST["name"])) {
					$nameErr = "Name is required";
				} else {
					$name = test_input($_POST["name"]);
					// check if name only contains letters and whitespace
				if (!preg_match("/^[a-zA-Z ]*$/",$name)) {
					$nameErr = "Only letters and white space allowed"; 
				}
			}
		*/
	?>
	
	<h2>PHP Form Validation Example</h2>
	<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		Name: <input type="text" name="name">
		<span class="error">* <?php echo $nameErr;?></span>
		Student ID: <input type="text" name="sid">
		<span class="error">* <?php echo $sidErr;?></span>
		E-mail: <input type="text" name="email">
		<span class="error">* <?php echo $emailErr;?></span>
		<br>
		Comment: <textarea name="comment" rows="5" cols="40"></textarea>
		<br><br>
		Gender:
		<input type="radio" name="gender" value="male">Male
		<input type="radio" name="gender" value="female">Female
		 <span class="error">* <?php echo $genderErr;?></span>
		<br><br>
		<input type="submit" name="submit" value="Submit">
	</form>
	
	<?php
		if (isset($_POST['submit'])) {
        // Submit-button was clicked
		echo "<h2>Your input:</h2>";
		echo $name;
		echo "<br>";
		echo $sid;
		echo "<br>";
		echo $email;
		echo "<br>";
		echo $comment;
		echo "<br>";
		echo $gender;
		}
	?>
	
</body>
</html>
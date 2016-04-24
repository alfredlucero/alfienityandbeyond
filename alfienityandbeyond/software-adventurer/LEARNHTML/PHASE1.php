<!-- <!DOCTYPE html> -->
<html lang="en-US"> <!-- important for accessibility applications and search engines -->
	<head>
		<title>PHASE1</title>
		<meta charset="UTF-8">
		<style type="text/css">
			a:link { color: white; background-color: transparent; text-decoration:none; }
			a:visited { color: white; background-color: transparent; text-decoration:none; }
			a:hover {color: white; background-color: transparent; text-decoration: underline; }
			a:active { color: blue; background-color: transparent; text-decoration: underline; }
			#footer {
				background-color:#006699;
				color:white;
				clear:both;
				text-align:center;
				padding:5px;
			}
			ul#menu {
				text-align: center;
				padding: 0;
			}
			ul#menu li{
				display:inline
			}
			ul#menu li a{
				background-color: black;
				color: white;
				padding: 10px 20px;
				text-decoration: none;
				border-radius 4px 4px 0 0;
			}
			ul#menu li a:hover{
				background-color: orange;
			}
		</style>
	</head>
	
	<body style="background-color:lightgrey"> 
		<h1 style="color:white; font-family:Georgia; text-align:center;">Alfred's First Step into Becoming the Next Great Front End Developer</h1>
		<p title='"FLUX" starts October 27, 2015' style="color:white; font-family:Georgia; text-align:center;">First paragraph into a new Beginning<br />
		<a href="http://www.w3schools.com">Learn with me here!</a><br/>
	
		<br />
		<br />
		<a href="http://github.com/alfredlucero"><img src="maybetomorrow.jpg" alt="maybetomorrow" style="width:500px;height:332px;border:0;"></a></p> <!-- border 0 to prevent IE 9 from adding a border -->
		<ul id="menu">
			<li><a href="http://www.w3schools.com/html/">HTML</a></li>
			<li><a href="http://www.w3schools.com/css/">CSS</a></li>
			<li><a href="http://www.w3schools.com/php/">PHP</a></li>
			<li><a href="http://www.w3schools.com/js/default.asp">JAVASCRIPT</a></li>
		</ul>
		<h2 id="top">Background</h2>
		<form action="PHASE1.html" method="GET">
			<fieldset>
				<legend>Personal Information:</legend>
				First name: <br />
				<input type="text" name="firstname"> <br />
				Last name: <br />
				<input type="text" name="lastname"> <br />
				<br />
				<input type="submit" name="submitButton" value="Submit">
				<br />
			</fieldset>
		</form>
		<?php 
			if ($_GET['submitButton']) {
				$first = $_GET['firstname'];
				$last = $_GET['lastname'];
				echo "<hr> Hello $first $last! Thanks for inputting your name!";
	
			}
		?>

		<br /><br /><br /><br /><br /><br /><br />
		<div id="footer">
			Copyright Alfred Lucero. <a href="#tops">Go back to the top</a>
		</div>
	</body>
	
</html>
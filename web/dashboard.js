function changeColorSelector(hexColor) {
    console.log(hexColor);
    var colsel = document.getElementById('colsel');
    colsel.style.backgroundColor = hexColor;

}

function hide() {
    return _hide.apply(this, arguments);
}

function _hide() {
    var signup = document.getElementById('signup');
    var login = document.getElementById('login');
    var content = document.getElementById('content');

    signup.style.display = '';
    login.style.display = '';
    content.style.display = '';

    for (var i = 0; i < arguments.length; i++){
	var itemString = arguments[i];

	if (itemString == 'signup') {
	    signup.style.display = 'none';
	} else if (itemString == 'login') {
	    login.style.display = 'none';
	} else if (itemString == 'content'){
	    content.style.display = 'none';
	}
    }

    return true;

}

function show() {
    return _show.apply(this, arguments);
}

function _show() {
    var signup = document.getElementById('signup');
    var login = document.getElementById('login');
    var content = document.getElementById('content');

    signup.style.display = 'none';
    login.style.display = 'none';
    content.style.display = 'none';

    for (var i = 0; i < arguments.length; i++){
	var itemString = arguments[i];

	if (itemString == 'signup') {
	    signup.style.display = '';
	    document.getElementsByTagName("body")[0].style.backgroundColor = "#ffffff";
	} else if (itemString == 'login') {
	    login.style.display = '';
	    document.getElementsByTagName("body")[0].style.backgroundColor = "#ffffff";
	} else if (itemString == 'content'){
	    content.style.display = '';
	}

    }

    return true;
}

function borderError(name) {
    document.getElementsByName(name)[0].style.borderColor = 'red';
}

function borderNormal(name) {
    document.getElementsByName(name)[0].style.borderColor = '#444444';
}

/*
 * Predicate is the function that tests whether or not an input
 * is invalid.
 *
 * Predicate returns true iff the item is invalid.
 * Predicate: String -> Boolean
 */
function validateItem(name, predicate, errMsg) {
    var form = document.forms["signup-form"];
    if (predicate(form[name].value)) {
	borderError(name);
	alert(errMsg);
	return false;
    } else {
	borderNormal(name);
	return true;
    }
}

ajax = new XMLHttpRequest();

function validateSignUp() {
    var form = document.forms["signup-form"];
    var valid = true;
    // Check first name
    valid = validateItem('fname', function(val){
	return val.length == 0;
    }, "Please enter a first name.") && valid;

    // Check last name
    valid = validateItem('lname', function(val){
	return val.length == 0;
    }, "Please enter a last name.") && valid;

    var pwdUidValidate = function (val) {
	return val.length > 15 || val.length < 8 || val.indexOf(' ') != -1;
    }

    // Check User ID
    valid = validateItem('uid', pwdUidValidate,
	 "Please enter a user ID between 8-15 characters with no spaces.") && valid;

    // Check for valid password
    valid = validateItem('pwd', pwdUidValidate,
	"Please enter a password between 8-15 characters with no spaces.") && valid;

    // Check if passwords match
    valid = validateItem('vpwd', function(val){
	return val != document.forms['signup-form']['pwd'].value;
    }, "The password entered do not match.") && valid;

    // Check email against simple regex
    valid = validateItem('email', function(val) {
	var emailRegex = new RegExp("^([^@]+[@][^@\.]+[.][0-9A-Za-x]{2,3})$");
	return !emailRegex.test(val);
    }, "Please enter a valid email") && valid;

    // Check for city selection
    var citysel = document.getElementById('citysel');
    var selectedItem = citysel.options[citysel.selectedIndex].value;
    if (selectedItem == 'noselect') {
	borderError('city');
	alert("Please select a city.");
	valid = false;
    } else {
	borderNormal('city');
    }

    // Check for color selection
    var colsel = document.getElementById('colsel');
    selectedItem = colsel.options[colsel.selectedIndex].value;
    if (selectedItem == 'noselect') {
	borderError('color');
	alert("Please select a color.");
	valid = false;
    } else {
	borderNormal('color');
    }

    // Check if user exists in DB
    if (valid) {
	ajax = new XMLHttpRequest();
	var args = 'fname=' + form['fname'].value + '&lname=' + form['lname'].value
	    + '&uid=' + form['uid'].value + '&pwd=' + form['pwd'].value + '&email='
	    + form['email'].value + '&city=' + form['city'].value + '&color='
	    + form['color'].value;
	console.log(args);
	ajax.onreadystatechange = function() {
	    if (ajax.readyState == 4 && ajax.status == 200) {
		console.log(ajax.responseText);
		if (ajax.responseText == "duplicate_user") {
		    // let user know there is an issue
		    valid = false;
		    borderError('uid');
		    alert("The user ID you chose is taken.");
		} else {
		    hide('signup');
		    show('login');
		    alert('Sign up successful!');
		}

	    }
	};

	ajax.open("POST", "php/signup.php", true);
	ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	ajax.send(args);
    }

    return valid;
}

function validateLogin() {
    var forms = document.forms['login'];
    if (forms['uid'].value.length > 0 && forms['pwd'].value.length > 0) {
	forms['uid'].style.borderColor = '#444444';
	forms['pwd'].style.borderColor = '#444444';

	return true;
    } else {
	forms['uid'].style.borderColor = '#ff0000';
	forms['pwd'].style.borderColor = '#ff0000';
	alert("Please enter a user name and password");
	return false;
    }
}

function getWeatherData() {

    var form = document.forms['login'];
    ajax = new XMLHttpRequest();
    ajax.onreadystatechange = function () {
	if (ajax.readyState == 4 && ajax.status == 200) {

	    if (ajax.responseText == "invalid_password") {
		form['pwd'].style.borderColor = "#ff0000";
		alert("Wrong password!");
		return;
	    }

	    form['pwd'].style.borderColor = "#444444";

	    console.log("callback running...");
	    console.log(ajax.responseText);
	    var jsonResponse =JSON.parse(ajax.responseText);
	    console.log(jsonResponse.fname);
	    console.log(jsonResponse.color);
	    var weather = JSON.parse(jsonResponse.weather);
	    console.log(weather);
	    console.log(weather.query);
	    var days = 5;
	    var fdw = weather.query.results.channel.item.forecast;
	    var fname = jsonResponse.fname;
	    var weatherContent = "";
	    for (var i = 0; i < days; i++) {
		weatherContent += '<li class="weatherItem">'
		    + '<div class="forecastTitle">' + fdw[i].day.charAt(0)
		    + '</div><div class="forecastDetail">' + fdw[i].text + '</div>'
		    + '<div class="forecastDegree">'+ fdw[i].high +  '</div></li>';
	    }


	    document.getElementById('weather-content').innerHTML = weatherContent;
	    document.getElementsByTagName("body")[0].style.backgroundColor = jsonResponse.color;
	    document.getElementById('main').innerHTML= "Welcome back " + fname + "!";
	    hide('login', 'signup');
	    show('content');
	}
    }

    var args = "uid=" + form['uid'].value + "&pwd=" + form['pwd'].value;
    console.log(args);
    ajax.open("POST", "php/weather.php", true);
    //ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    ajax.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    ajax.send(args);

    console.log("ajax request sent");
    console.log(ajax.responseText);
    return true;
}

function sendLogin() {
    return validateLogin() && getWeatherData();
}

function update() {
    ajax = new XMLHttpRequest();
    ajax.onreadystatechange = function () {
	if (ajax.readyState == 4 && ajax.status == 200) {

	    // Handle error; probably shouldn't happen for this app.
	    console.log("callback running...");
	    console.log(ajax.responseText);

	    var jsonResponse =JSON.parse(ajax.responseText);
	    var components = "<ul>";
	    for (var key in jsonResponse) {
		components +=
		'<li class="component">'
		    + '<div class="component-title">' + key + '</div>'
		    + '<div class="component-content">'
		    + jsonResponse[key].pid_value
		    + '<br>'
		    + jsonResponse[key].pid_units
		    + '</div>'
		    + '</li>';
	    }
	    components += '</ul>';
	    document.getElementById("content-inner").innerHTML = components;
	}
    }

    ajax.open("GET", "/dashboard_update.php");
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

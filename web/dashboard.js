// This is a global list of PIDs that the user has requested.
target_pids = [];
available_pids = {};

// Generates the card that displays data for this pid.
function generateCard(name, value, units) {
    return '<li class="component" id="' + name + '">'
	+ '<div class="component-title">' + name + '</div>'
	+ '<div class="component-content">'
	+ value + '<br>'+ units+ '</div>'+ '</li>';
}

// Hides an element.
function hide(id) {
    document.getElementById(id).style.display = 'none';
}

// Shows an element.
function show(id) {
    document.getElementById(id).style.display = 'block';
}

// Either shows or hides the pid selector dropdown.
function togglePidSelector() {
    var pidsel = document.getElementById('pidsel');

    if (pidsel.style.display == '' || pidsel.style.display == 'none') {
	show('pidsel');
    } else {
	hide('pidsel');
    }
}

function resetPidSelector(sel) {
    sel.selectedIndex = 0;
}

// Registers a pid to fetch information for. The next AJAX request
// after this pid has been registered will have the information.
function registerPid() {
    var sel = document.getElementById("pidsel");
    var pid = (sel.options[sel.selectedIndex].value);

    if (pid === null || pid == "" || sel.selectedIndex <= 0) {
	resetPidSelector(sel);
	hide('pidsel');
	return;
    }

    var index = target_pids.indexOf(pid);
    if (index == -1) {
	 target_pids.push(sel.options[sel.selectedIndex].value);
    } else {
	// Hide element. It will be deleted on next update.
	hide(sel.options[sel.selectedIndex].text);
	target_pids.splice(index, 1);
	resetPidSelector(sel);
	hide('pidsel');
	return;
    }
    // How to get units?
    var newCard = generateCard(available_pids[pid].name, "&nbsp;",
			      available_pids[pid].units);
    document.getElementById("content-list").innerHTML += newCard;
    resetPidSelector(sel);
    hide('pidsel');
}

// Updates information for all registered pids.
function update() {
    var ajax = new XMLHttpRequest();
    ajax.onreadystatechange = function () {
	if (ajax.readyState == 4) {
	    if (ajax.status == 200) {
		// Handle error; probably shouldn't happen for this app.
		console.log("callback running...");
		console.log(ajax.responseText);
		var jsonResponse =JSON.parse(ajax.responseText);
		var components = "";
		for (var key in jsonResponse) {
		    components += generateCard(key,
					       jsonResponse[key].pid_value,
					       jsonResponse[key].pid_units);
		}
		document.getElementById("content-list").innerHTML = components;
	    }
	    setTimeout(function() { update(); }, 1);
	}
    }


    var urlParams = "";
    if (target_pids.length > 0) {
	var param = "pid[]=";
	urlParams = "?" + param + target_pids.join("&" + param);
    }

    console.log(urlParams);
    var fullUrl =  "/dashboard_update.php" + urlParams;
    console.log(fullUrl);
    ajax.open("GET", fullUrl);
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

// Creates the option element for the available pids.  This was done to
// decouple the index page from a PHP implementation and instead focus on
// being more RESTful.
function generateOption(pid, name) {
    return '<option value="' + pid + '">' + name + '</option>';
}

// Gets the available pids from the server. The json response is of format
// pid:string -> {name:string, units:string}
function getAvailablePids() {
    var ajax = new XMLHttpRequest();
    ajax.onreadystatechange = function () {
	if (ajax.readyState == 4) {
	    if (ajax.status == 200) {
		// Handle error; probably shouldn't happen for this app.
		console.log("parsing available pids...");
		console.log(ajax.responseText);
		var jsonResponse =JSON.parse(ajax.responseText);
		// response maps pid -> {name, units}.
		available_pids = jsonResponse;
		var options = '<option value=""> -- Please select a PID -- </option>';
		for (var key in jsonResponse) {
		    options += generateOption(key, jsonResponse[key].name);
		}

		document.getElementById("pidsel").innerHTML = options;

	    }
	}
    }

    ajax.open("GET", "/dashboard_available_pids.php");
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

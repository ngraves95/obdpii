// This is a global list of PIDs that the user has requested.
target_pids = [];

function generateCard(name, value, units) {
    return '<li class="component" id="' + name + '">'
	+ '<div class="component-title">' + name + '</div>'
	+ '<div class="component-content">'
	+ value + '<br>'+ units+ '</div>'+ '</li>';
}

function hide(id) {
    document.getElementById(id).style.display = 'none';
}

function show(id) {
    document.getElementById(id).style.display = 'block';
}

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

function registerPid(sel) {
    var pid = (sel.options[sel.selectedIndex].value);

    if (pid === null || pid == "") {
	resetPidSelector(sel);
	togglePidSelector();
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
	togglePidSelector();
	return;
    }

    // How to get units?
    var newCard = generateCard(sel.options[sel.selectedIndex].text, "", "");
    document.getElementById("content-list").innerHTML += newCard;
    resetPidSelector(sel);
    togglePidSelector();
}

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
		components += "";
		document.getElementById("content-list").innerHTML = components;
	    }
	    setTimeout(function() { update(); }, 50000);
	}
    }

    ajax.open("GET", "/dashboard_update.php");
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

function generateCard(name, value, units) {
    return '<li class="component">'
	+ '<div class="component-title">' + name + '</div>'
	+ '<div class="component-content">'
	+ value + '<br>'+ units+ '</div>'+ '</li>';
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
		var components = "<ul>";
		for (var key in jsonResponse) {
		    components += generateCard(key,
					       jsonResponse[key].pid_value,
					       jsonResponse[key].pid_units);
		}
		components += "</ul>";
		document.getElementById("content-inner").innerHTML = components;
	    }
	    setTimeout(function() { update(); }, 1000);
	}
    }

    ajax.open("GET", "/dashboard_update.php");
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

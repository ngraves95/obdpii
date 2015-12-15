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
	    setTimeout(function() { update(); }, 1000);
	}
    }

    ajax.open("GET", "/dashboard_update.php");
    ajax.setRequestHeader("Content-type","application/text");
    ajax.send();
}

const char page_index[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>

<style type="text/css">

* {
    -webkit-box-sizing: border-box;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
}

*:before, *:after {
    -webkit-box-sizing: border-box;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
}

*:before, *:after {
    -webkit-box-sizing: border-box;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
}

h2, .h2 {
    font-size: 30px;
}

h1, .h1, h2, .h2, h3, .h3 {
    margin-top: 20px;
    margin-bottom: 10px;
}

h3, .h3 {
    font-size: 24px;
}

h1, h2, h3, h4, h5, h6, .h1, .h2, .h3, .h4, .h5, .h6 {
    font-family: inherit;
    font-weight: 500;
    line-height: 1.1;
    color: inherit;
}

html {
    font-size: 10px;
    -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
    font-family: sans-serif;
    -ms-text-size-adjust: 100%;
    -webkit-text-size-adjust: 100%;
}

body {
    font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
    font-size: 14px;
    line-height: 1.42857143;
    color: #333333;
    background-color: #ffffff;
}

hr {
    -webkit-box-sizing: content-box;
    -moz-box-sizing: content-box;
    box-sizing: content-box;
    height: 0;
    margin-top: 20px;
    margin-bottom: 20px;
    border: 0;
    border-top: 1px solid #eeeeee;
}

.container {
    margin-right: auto;
    margin-left: auto;
    padding-left: 15px;
    padding-right: 15px;
}

.btn {
    display: inline-block;
    margin-bottom: 0;
    font-weight: normal;
    text-align: center;
    vertical-align: middle;
    -ms-touch-action: manipulation;
    touch-action: manipulation;
    cursor: pointer;
    background-image: none;
    border: 1px solid transparent;
    white-space: nowrap;
    padding: 6px 12px;
    font-size: 14px;
    line-height: 1.42857143;
    border-radius: 4px;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
}

.btn-primary {
    color: #ffffff;
    background-color: #337ab7;
    border-color: #2e6da4;
}

button {
    overflow: visible;
}

.plusbtn {
  text-shadow: 1px 1px 3px #666666;
  box-shadow: 0px 1px 3px #666666;
  font-family: Arial;
  color: #ffffff;
  background: #00d118;
  text-decoration: none;
  width: 34px;
  height: 34px;
}

.minusbtn {
  text-shadow: 1px 1px 3px #666666;
  box-shadow: 0px 1px 3px #666666;
  font-family: Arial;
  color: #ffffff;
  background: #cf0000;
  text-decoration: none;
  width: 34px;
  height: 34px;
}

.btn:hover {
  text-decoration: none;
}

.text-center{
  text-align: center;
}

.input-text{
  text-align: center;
    width: 45%;
    max-width: 300px;
    height: 34px;
    padding: 6px 12px;
    font-size: 14px;
    line-height: 1.42857143;
    color: #555555;
    background-color: #ffffff;
    background-image: none;
    border: 1px solid #cccccc;
    border-radius: 4px;
    -webkit-box-shadow: inset 0 1px 1px rgba(0, 0, 0, 0.075);
    box-shadow: inset 0 1px 1px rgba(0, 0, 0, 0.075);
    -webkit-transition: border-color ease-in-out .15s, -webkit-box-shadow ease-in-out .15s;
    -o-transition: border-color ease-in-out .15s, box-shadow ease-in-out .15s;
    transition: border-color ease-in-out .15s, box-shadow ease-in-out .15s;
}

.manual-input{
  width: 60%;
  max-width: 300px;
}
}

</style>


<script>

window.onload = function(){

  //empty object for modified settings
  var new_settings = {};

  //set up http request
  var request = new XMLHttpRequest();
  var url = "/api/configurations";

  request.open("GET", url, false);
  request.send();
  var settings = JSON.parse(request.responseText);
  page_setup(settings);

  //get all modifier buttons
  //each + and - button has contains class "modifier"
  //each of these buttons is attached to appropriate field through a name
  //button name = id of the field it's attached to
  //increment/decrement value is attached to each button
  var buttons = document.getElementsByClassName("modifier");

  //check for onclicks on each modifier button
  for(var i = 0; i < buttons.length; i++){
    buttons[i].onclick = function(e){
      //get field from which the button is attached to
      var field = document.getElementById(this.getAttribute("name"));

      //conversion to numbers to increment/decrement
      var temp = Number(field.value);
      field.value = Number(this.value) + temp;

      new_settings[this.getAttribute("name")] = Number(field.value);
    }
  }

  //check for manual inputs onchange
  var inputs = document.getElementsByTagName('input');

  for (var i = 0; i < inputs.length; i++){
    inputs[i].onchange = function(){
      new_settings[this.id] = this.value;
    }
  }
  

  //handle save settings button
  document.getElementById("submit_settings").onclick = function(){
    
    var save_url = "/save";
    save_url += "?" + Object.keys(new_settings).map(function(k) {
    return encodeURIComponent(k) + '=' + encodeURIComponent(new_settings[k])
    }).join('&');

    window.location.href = save_url;
  }

}

function page_setup(data){
  for (var key in data){
    document.getElementById(key).value = data[key];
  }
}
</script>


<head>
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
</head>

<body>
<div class="container text-center">

<h2>Naze32 Configuration</h2>

<form action="/dump">
  <input type="submit" class="btn btn-primary" value="All Configurations">
</form>

<h3>Looptime</h3>
<button name="looptime" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="looptime" type="text" class="input-text">
<button name="looptime" class="modifier btn plusbtn" type="button" value="1">+</button>

<hr>

<h3>Pitch - P</h3>
<button name="p_pitch" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="p_pitch" type="text" class="input-text">
<button name="p_pitch" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Pitch - I</h3>
<button name="i_pitch" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="i_pitch" type="text" class="input-text">
<button name="i_pitch" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Pitch - D</h3>
<button name="d_pitch" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="d_pitch" type="text" class="input-text">
<button name="d_pitch" class="modifier btn plusbtn" type="button" value="1">+</button>

<hr>

<h3>Roll - P</h3>
<button name="p_roll" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="p_roll" type="text" class="input-text">
<button name="p_roll" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Roll - I</h3>
<button name="i_roll" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="i_roll" type="text" class="input-text">
<button name="i_roll" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Roll - D</h3>
<button name="d_roll" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="d_roll" type="text" class="input-text">
<button name="d_roll" class="modifier btn plusbtn" type="button" value="1">+</button>

<hr>

<h3>Yaw - P</h3>
<button name="p_yaw" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="p_yaw" type="text" class="input-text">
<button name="p_yaw" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Yaw - I</h3>
<button name="i_yaw" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="i_yaw" type="text" class="input-text">
<button name="i_yaw" class="modifier btn plusbtn" type="button" value="1">+</button>

<h3>Yaw - D</h3>
<button name="d_yaw" class="modifier btn minusbtn" type="button" value="-1">-</button>
<input id="d_yaw" type="text" class="input-text">
<button name="d_yaw" class="modifier btn plusbtn" type="button" value="1">+</button>

<br>
<br>

<button id="submit_settings" class="btn btn-primary" type="button">Save Settings</button>

<hr>

<h2>Manual Configuration</h2>
<form action="/manualconfig" method="get">
  <input type="text" class="input-text manual-input" name="command" placeholder="Enter Command">
  <br>
  <br>
  <input type="submit" class="btn btn-primary">
</form>

</div>

</body>

</html>

)=====";

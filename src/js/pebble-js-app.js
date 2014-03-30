Pebble.addEventListener("ready",
    function(e) {
        console.log("READY");
    }
);
Pebble.addEventListener("showConfiguration",
  function(e) {
    Pebble.openURL("http://adamh.me/projects/stockwatch/configurable.html");
  }
);
Pebble.addEventListener("webviewclosed",
  function(e) {
    var configuration = JSON.parse(e.response);
    console.log(e.response);
    Pebble.sendAppMessage(configuration);
  }
);
Pebble.addEventListener("ready",
    function(e) {
        console.log("Hello world! - Sent from your javascript application.");
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
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

var token = "YZtE5zbjX7GGBgDMJvVzo0vhTfnt";

function sendStuff(quote)
{
   var msg = {}
   msg[0] = JSON.stringify(quote.symbol);
   msg[1] = JSON.stringify(quote.open);
   msg[2] = JSON.stringify(quote.high);
   msg[3] = JSON.stringify(quote.low);
   msg[4] = JSON.stringify(quote.close);
   msg[5] = JSON.stringify(quote.last);
   console.log("Sending info! " + JSON.stringify(msg));
   Pebble.sendAppMessage(msg);
}

// Fetch stock data for a given stock symbol
function fetchStockQuote(symbol, isInitMsg)
{
   var response;
   var req = new XMLHttpRequest();
   console.log("I did a thing!");
   // build the GET request
   req.open('GET', "https://api.tradier.com/v1/markets/quotes?symbols=" + symbol, true);
   req.onload = function(e) {
      if (req.readyState == 4)
      {
         // 200 - HTTP OK
         if(req.status == 200)
         {
            console.log(req.responseText);
            response = JSON.parse(req.responseText);
            if (response.quotes)
            {
               console.log("Quotes!");
               var q = response.quotes.quote;
               if (q instanceof Array)
               {
                  var len = q.length;
                  for(var i=0;i<len;i++)
                     sendStuff(q);
               }
               else
                  sendStuff(q);
            }
         }
         else
            console.log("Request returned error code " + req.status.toString());
      }
   };
   req.setRequestHeader("Authorization", "Bearer " + token);
   req.setRequestHeader("Accept", "application/json")
   req.send(null);
}

// Set callback for the app ready event
Pebble.addEventListener("ready", function(e) {
   console.log("connect! " + e.ready);
   console.log(e.type);
   /*// Fetch saved symbol from local storage (using
   // standard localStorage webAPI)
   symbol = localStorage.getItem("symbol");
   if (!symbol)
      symbol = "FB";
   var isInitMsg = true;
   fetchStockQuote(symbol, isInitMsg);
   console.log("CHECK CALL");*/
});

// Set callback for appmessage events
Pebble.addEventListener("appmessage", function(e) {
   console.log("message");
   if (e.payload.symbol)
   {
      console.log("Symbol! " + e.payload.symbol);
      symbol = e.payload.symbol;
      localStorage.setItem("symbol", symbol);
      isInitMsg = false;
      fetchStockQuote(symbol, isInitMsg);
   }
   else
      console.log("No symbol!");
});

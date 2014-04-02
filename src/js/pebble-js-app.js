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

function sendStuff(quote)
{
   if (quote.Open)
   {
      console.log("Sending:")
      for (var i in quote)
         console.log(i + " = " + quote[i]);
      Pebble.sendAppMessage(msg);
   }
   else
      console.log("Invalid quote to send! " + quote.symbol);
}

// Fetch stock data for a given stock symbol
function fetchStockQuote(symbol)
{
   if (symbol.length == 0)
   {
      console.log("No symbols provided!")
      return;
   }
   var symbollist = "\"" + symbol.split(",").join("\",\"") + "\"";
   console.log("fetching data for symbols: " + symbollist);
   var response;
   var req = new XMLHttpRequest();

   var values = ["Open", "Ask", "Change", "PercentChange"];
   //var values = ["*"];
   // build the GET request
   req.open('GET', "http://query.yahooapis.com/v1/public/yql?q=select " + values.join() + " from yahoo.finance.quotes where symbol in (" + symbollist + ")%0A%09%09&env=http%3A%2F%2Fdatatables.org%2Falltables.env&format=json", true);
   req.onload = function(e) {
      if (req.readyState == 4)
      {
         // 200 - HTTP OK
         if(req.status == 200)
         {
            console.log(req.responseText);
            response = JSON.parse(req.responseText);
            var results = response.query.results
            if (results)
            {
               var quotes = results.quote;
               if (quotes instanceof Array)
               {
                  var len = quotes.length;
                  for(var i=0;i<len;i++)
                     sendStuff(quotes[i]);
               }
               else
                  sendStuff(quotes);
            }
            else
               console.log("Invalid stuff to send! " + symbol);
         }
         else
            console.log("Request returned error code " + req.status.toString());
      }
   };
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

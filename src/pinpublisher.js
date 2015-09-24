var dogs = Array();
var states = Array();


Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
    
    
    dogs[0]="Desti";
    dogs[1]="Eksi";
    dogs[2]="Falka";

    states[0]="Nic";
    states[1]="Sikała";
    states[2]="Robiła";
    states[3]="Komplet";
  }
);


Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received message: ' + JSON.stringify(e.payload));
    
    var body="";
    for (k in e.payload) {
      body+=dogs[k]+": ";
      body+=states[e.payload[k]] + "\n";
    }
    
    var date = new Date();
    var pin={
      "id": "jhpin-"+ Math.round((Math.random() * 100000)),
      "time": date.toISOString(),
      "layout": {
        "type": "genericPin",
        "title": "Psi Spacer",
        "tinyIcon": "system://images/REACHED_FITNESS_GOAL",
        "body": body
      }
    };
    console.log('Inserting pin: ' + JSON.stringify(pin));
    insertUserPin(pin, function(responseText) { 
      console.log('Result: ' + responseText);
      var transactionId = Pebble.sendAppMessage( { '99': responseText },
          function(e) {
            console.log('Successfully delivered message with transactionId='
              + e.data.transactionId);
          },
          function(e) {
            console.log('Unable to deliver message with transactionId='
              + e.data.transactionId
              + ' Error is: ' + e.error.message);
          }
        );
            });
  }
);

/*{
  "id": "cloudpebble-test-pin-4",
  "time": "2015-08-30T21:35:00Z",
  "layout": {
    "type": "genericPin",
    "title": "Psi Spacer",
    "tinyIcon": "system://images/REACHED_FITNESS_GOAL",
    "body": "Desti: Sikała\nEksi: Komplet\nFalka: Robiła"
  }
}*/
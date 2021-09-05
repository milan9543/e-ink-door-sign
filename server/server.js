// server.js
//
// Used for sending image data to the e-ink door sign
//
// author: stf

// for accessing server-side files
var http = require('http');
var https = require('https');
var fs = require('fs');

var path = require('path');
var cdir = process.cwd();

const WebSocket = require('ws');

// the express webserver
const express = require('express');
const app = express();

var httpServer = http.createServer(app);
httpServer.listen(4000);

const { exec } = require("child_process");

// backend websocket server -- the uP connects here 
const be_wss = new WebSocket.Server({port: 1234});


//function saveCSV(data, groupnum) {
//   var formattedNumber = ("0" + groupnum).slice(-2); // to get two digits
//
//   if(fs.existsSync('./G'+formattedNumber+".csv")) {
//       fs.unlinkSync('./G'+formattedNumber+".csv");
//   }
//
//   fs.writeFile("G"+formattedNumber+".csv", "# ID, TIMESTAMP\n", function (err) {
//        if (err) throw err;
//   });
//
//   var times = [];
//   var ids   = [];
//   for(var i=0; i<256; i++){
//     if(i==0)
//         times[i] = BigInt(data[(i+1)*12 + 7] << 56 | data[(i+1)*12 + 6] << 48 | data[(i+1)*12 + 5] << 40 | data[(i+1)*12 + 4] << 32 | data[(i+1)*12 +3] << 24 | data[(i+1)*12 + 2] << 16 | data[(i+1)*12 + 1] << 8 | data[(i+1)*12]);
//     else
//         times[i] = times[i-1] + BigInt(data[(i+1)*12 + 7] << 56 | data[(i+1)*12 + 6] << 48 | data[(i+1)*12 + 5] << 40 | data[(i+1)*12 + 4] << 32 | data[(i+1)*12 +3] << 24 | data[(i+1)*12 + 2] << 16 | data[(i+1)*12 + 1] << 8 | data[(i+1)*12]);
//         ids[i]   = data[(i+1)*12 +11] << 24 | data[(i+1)*12 + 10] << 16 | data[(i+1)*12 + 9] << 8 | data[(i+1)*12 + 8];
//
//     var line = ids[i] + "," + times[i] + "\n"; 
//     fs.appendFile("G"+formattedNumber+".csv", line, function (err) {
//        if (err) throw err;   
//     });  
//
//   }
//}

function os_func() {
    this.execCommand = function(cmd, callback) {
        exec(cmd, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`);
                return;
            }

            callback(stdout);
        });
    }
}
var os = new os_func();

// current default -- pass all messages from the backend to the frontend
// backend server logic
be_wss.binaryType = 'arraybuffer'
be_wss.on('connection', function connection(be_ws) {
    console.log("Backend connected...");
    
    os.execCommand("./prep_b.sh", function(returnvalue) {
	    let rawdata_b = fs.readFileSync('_tmp/data_b.json');
	    let data_b_json = JSON.parse(rawdata_b);  

	    let rawdata_r = fs.readFileSync('_tmp/data_r.json');
	    let data_r_json = JSON.parse(rawdata_r);  
	
	    // First black image packet
	    var image_data = new Uint8Array(16384);
	    for(var i=0; i<16384; i++){
	        image_data[i] = data_b_json.data[i];
	    }

	    be_wss.clients.forEach(function each(client) {
		client.send(image_data.buffer);
	    });

	    // Second black image packet
	    for(var i=0; i<16384; i++){
	        image_data[i] = data_b_json.data[i + 16384*1];
	    }

	    be_wss.clients.forEach(function each(client) {
	        client.send(image_data.buffer);
	    });

	    // Final black image packet
	    for(var i=0; i<15232; i++){
	        image_data[i] = data_b_json.data[i + 16384*2];
	    }

	    be_wss.clients.forEach(function each(client) {
	        client.send(image_data.buffer);
	    });

	    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	    // First red image packet
	    for(var i=0; i<16384; i++){
	        image_data[i] = data_r_json.data[i];
	    }

	    be_wss.clients.forEach(function each(client) {
		client.send(image_data.buffer);
	    });

	    // Second red image packet
	    for(var i=0; i<16384; i++){
	        image_data[i] = data_r_json.data[i + 16384*1];
	    }

	    be_wss.clients.forEach(function each(client) {
	        client.send(image_data.buffer);
	    });

	    // Final red image packet
	    for(var i=0; i<15232; i++){
	        image_data[i] = data_r_json.data[i + 16384*2];
	    }

	    be_wss.clients.forEach(function each(client) {
	        client.send(image_data.buffer);
	    });

	    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    });


});


console.log("Server is running: http://localhost:4000");

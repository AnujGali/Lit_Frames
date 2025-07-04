// connect to the broker 
const client = mqtt.connect('ws://broker.hivemq.com:8000/mqtt'); 

// in case of error, display message 
client.on('error', (err) => {
    document.getElementById('status').innerText = `Connection error: ${err}`;
}); 

document.getElementById('publishBtn').addEventListener('click', () => {
    // obtain the message and the specified microcontroller 
    const message = document.getElementById('message').value;
    const topic = document.getElementById('microcontroller').value; 

    // publish the message based on the topic
    if(message && topic) {
    client.publish(topic, message);  
    } else {
        document.getElementById('status').innerText = "Please enter a message and select a microcontroller.";
    }
}); 
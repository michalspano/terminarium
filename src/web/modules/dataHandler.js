// function handling incoming messages
function handleData(data) {
  const db = app.database();

  const messageData = {
    timestamp: Date.now(),
    payload: data
  };

  // FOR EXAMPLE
  // write incoming data to Firebase Realtime Database
  db.ref('messages').push(messageData, function (error) {
    if (error) {
      console.error('Error sending data to Firebase:', error);
    } else {
      console.log('Data written to Firebase successfully!');
    }
  });
}

// export handleData function for use in other modules
module.exports = {
  handleData
};
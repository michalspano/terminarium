// *** Vite Environment Variables ***
// These variables are used to establish a connection to the Firebase Realtime Database.

const ENV = import.meta.env;

/** 
 * @const {Object} firebaseConfig
 * The firebase configuration object is represented by secrets obtained from the 
 * .env file; thus, integrity of the firebase configuration is maintained. The configuration
 * values are shared with the team members via a secure channel and/or obtained from the Google
 * Firebase Console. */
export const firebaseConfig = {
  apiKey:             ENV.VITE_API_KEY,
  authDomain:         ENV.VITE_AUTH_DOMAIN,
  databaseURL:        ENV.VITE_DATABASE_URL,
  projectId:          ENV.VITE_PROJECT_ID,
  storageBucket:      ENV.VITE_STORAGE_BUCKET,
  messagingSenderId:  ENV.VITE_MESSAGING_SENDER_ID,
  appId:              ENV.VITE_APP_ID,
  measurementId:      ENV.VITE_MEASUREMENT_ID,
};
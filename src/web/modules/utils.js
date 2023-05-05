// utils.js - shared states and behaviors across modules

import { config as dotEnvConfig } from "dotenv";    // import dotenv configuration (aliased)

dotEnvConfig(); // initialize dotenv configuration

/** 
 * @const {Object} firebaseConfig
 * The firebase configuration object is represtented by secrets obtained from the 
 * .env file; thus, integrity of the firebase configuration is maintained. The configuration
 * values are shared with the team members via a secure channel and/or obtained from the Google
 * Firebase Console. */
export const firebaseConfig = {
  apiKey:             process.env.API_KEY,
  authDomain:         process.env.AUTH_DOMAIN,
  databaseURL:        process.env.DATABASE_URL,
  projectId:          process.env.PROJECT_ID,
  storageBucket:      process.env.STOREAGE_BUCKET,
  messagingSenderId:  process.env.MESSAGING_SENDER_ID,
  appId:              process.env.APP_ID,
  measurementId:      process.env.MEASUREMENT_ID,
};
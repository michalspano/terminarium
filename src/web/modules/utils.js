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
  apiKey: "AIzaSyCWIfIxCsDlNLQ6nCYULfo6mNGGYluhGcE",
  authDomain: "terminariumdb.firebaseapp.com",
  databaseURL: "https://terminariumdb-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "terminariumdb",
  storageBucket: "terminariumdb.appspot.com",
  messagingSenderId: "1081373991193",
  appId: "1:1081373991193:web:cd7ae25f728527f5daa588",
  measurementId: "G-9PJPD4TWZQ"
};
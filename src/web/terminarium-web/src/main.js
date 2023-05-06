import { createApp } from 'vue'
import App from './App.vue'
import VuePlyr from 'vue-plyr'
import 'vue-plyr/dist/vue-plyr.css'
import "@fontsource/cantora-one"

createApp(App)
    .use(VuePlyr, {
        plyr: {}
    })
    
    .mount('#app')

    

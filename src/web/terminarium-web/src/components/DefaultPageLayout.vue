<!----------------------------------*COMPONENT DESCRIPTION*-------------------------------------
    This component contains the default page layout which will always be displayed to the user.
    ***Any change made here will affect the entire website!***
----------------------------------------------------------------------------------------------->

<script setup>
import Header from './Header.vue';
import Footer from './Footer.vue';
import Background from './Background.vue';
</script>


<template>
    <div id="defaultLayout">
        <section class="container">
            <Header></Header>
        </section>
        <section class="container">
            <Footer></Footer>
        </section>
        <Background></Background>
    </div>
</template>


<script>
export default {
    name: "DefaultPageLayout"
}
</script>

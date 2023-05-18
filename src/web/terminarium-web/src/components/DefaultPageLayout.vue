<!----------------------------------*COMPONENT DESCRIPTION*-------------------------------------
    This component contains the default page layout which will always be displayed to the user.
    ***Any change made here will affect the entire website!***
----------------------------------------------------------------------------------------------->

<script setup>
import SiteHeader from './Header.vue';
import SiteFooter from './Footer.vue';
import Background from './Background.vue';
</script>


<template>
    <div id="defaultLayout">
        <section class="container">
            <SiteHeader @accessButtonEvent="$emit('accessButtonEvent')" />
        </section>
        <section class="container">
            <SiteFooter/>
        </section>
        <Background></Background>
    </div>
</template>


<script>
export default {
    name: "DefaultPageLayout",
    components: {
        SiteHeader,
        SiteFooter,
        Background
    },
}
</script>

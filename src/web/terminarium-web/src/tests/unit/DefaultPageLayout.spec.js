/***************************************************************************************************
 * Terminarium (test suite)
 * File: {@code DefaultPageLayout.spec.js}
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// Import the test suite functionality
import { shallowMount } from '@vue/test-utils';
import { describe, it, expect } from 'vitest';

// Import the sub-components that are being tested
import Header from '@/components/Header.vue';
import Footer from '@/components/Footer.vue';
import Background from '@/components/Background.vue';

// Import the main component that is being tested
import DefaultLayout from '@/components/DefaultPageLayout.vue';

describe('Check that the sub-components are being imported properly', () => {
    it('should import Header', () => {
        expect(Header).toBeDefined();
    });

    it('should import Footer', () => {
        expect(Footer).toBeDefined();
    });

    it('should import Background', () => {
        expect(Background).toBeDefined();
    });
});

describe('Check that (sub-)components are being rendered', () => {
    const wrapper = shallowMount(DefaultLayout);

    it('should exist', () => {
        expect(wrapper.exists()).toBe(true);
    });

    it('should render Header', () => {
        expect(wrapper.findComponent(Header).exists()).toBe(true);
    });

    it('should render Footer', () => {
        expect(wrapper.findComponent(Footer).exists()).toBe(true);
    });

    it('should render Background', () => {
        expect(wrapper.findComponent(Background).exists()).toBe(true);
    });
});

describe('Check that the structure of the component is correct', () => {
    const wrapper = shallowMount(DefaultLayout);

    // The sub-components should be wrapped inside a class with id "defaultLayout"
    it('should have a class with id "defaultLayout"', () => {
        expect(wrapper.find('#defaultLayout').exists()).toBe(true);
    });

    it('should have the Header inside a class with id "defaultLayout"', () => {
        expect(wrapper.find('#defaultLayout').findComponent(Header).exists()).toBe(true);
    });

    it('should have the Footer inside a class with id "defaultLayout"', () => {
        expect(wrapper.find('#defaultLayout').findComponent(Footer).exists()).toBe(true);
    });

    it('should have the Background inside a class with id "defaultLayout"', () => {
        expect(wrapper.find('#defaultLayout').findComponent(Background).exists()).toBe(true);
    });
    
    // The component should have at leat 2 sections with the class "container" (one for the Header and one for the Footer)
    it('should have at least 2 sections with the class "container"', () => {
        expect(wrapper.findAll('section.container').length).toBeGreaterThanOrEqual(2);
    });

    // The Header is wrapped in a section with class "container" in the first instance of such a section
    it('should have a section with class "container" that contains the Header component', () => {
        expect(wrapper.findAll('section.container').at(0).findComponent(Header).exists()).toBe(true);
    });

    // Afterwards, the Footer is wrapped in a section with class "container"
    it('should have a section with class "container" that contains the Footer component', () => {
        expect(wrapper.findAll('section.container').at(1).findComponent(Footer).exists()).toBe(true);
    });

});
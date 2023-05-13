/***************************************************************************************************
 * Terminarium (test suite)
 * File: {@code Header.spec.js}
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// Import the test suite functionality
import { shallowMount } from '@vue/test-utils';
import { describe, it, expect } from 'vitest';

// Import components that are part of the testing
import Header from '@/components/Header.vue'
import AccessButton from '@/components/AccessButton.vue'

describe('Check that components are defined', () => {
    it('should import Header', () => {
        expect(Header).toBeDefined()
    });
    it('should import AccessButton', () => {
        expect(AccessButton).toBeDefined()
    });
});

describe('Check that components are rendered and the structure is adhered to', () => {
    const wrapper = shallowMount(Header);   // Define the Header component as a wrapper

    it('should exist', () => {
        expect(wrapper.exists()).toBe(true);
    });

    it('should render the logo inside the logo_container class with alt attribute', () => {
        expect(wrapper.find('.logo_container img').exists()).toBe(true);
        expect(wrapper.find('.logo_container img').attributes('alt')).not.toBe('');
    });

    it('should render the AccessButton (as a child) inside header_button class', () => {
        // Include the AccessButton component in the test as a child of Header
        const modifiedWrapper = shallowMount(Header, {
            global: { components: { AccessButton } }
        });

        expect(modifiedWrapper.find('.header_button').findComponent(AccessButton).exists()).toBe(true);
    });

});

/**
 * Note: the current convention is that the header should have only 3 links when
 * the user is not logged in, and 7 links when the user is logged in (inside the 
 * "header_nav_bar" nav class). Furthermore, the text of the AccessButton changes; 
 * however, that is covered in the AccessButton test suite.
 */
describe('Check the logic based on the logged in status', () => {
    /* This class shall be used to store the <a/> links
     * and its text, and is thus necessary */
    it('should have a nav class "header_nav_bar"', () => {
        const wrapper = shallowMount(Header);
        expect(wrapper.find('.header_nav_bar').exists()).toBe(true);
    });

    it('should render the correct type when user is not logged in', () => {
        const wrapper = shallowMount(Header, {
            data() {
                return {
                    isLoggedIn: false
                }
            }
        });
        expect(wrapper.findAll('.header_nav_bar a').length).toBe(3);
    });

    it('should render the correct type when user is logged in', () => {
        const wrapper = shallowMount(Header, {
            data() {
                return {
                    isLoggedIn: true
                }
            }
        });
        expect(wrapper.findAll('.header_nav_bar a').length).toBe(7);
    });
});

// TODO: add a check to ensure that the links are valid (i.e. they point to the correct destinations)
// TODO: add any additional tests that are necessary to ensure that the header is working as intended
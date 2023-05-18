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
    // Create a wrapper with the global provide property set to false
    // For this scope of the test, we are not concerned with the value of isLoggedIn (however, it is required)
    const wrapper = shallowMount(Header, {
        global: {
            provide: { isLoggedIn: { value: false } }
        }
    });

    it('should exist', () => {
        expect(wrapper.exists()).toBe(true);
    });

    it('should render the logo inside the logo_container class with alt attribute', () => {
        expect(wrapper.find('.logo_container img').exists()).toBe(true);
        expect(wrapper.find('img').attributes('src')).toBe('/src/assets/terminarium-logo.png');
        expect(wrapper.find('.logo_container img').attributes('alt')).not.toBe('');
    });
});

describe('Check AccessButton child component', () => {
    it('should render the AccessButton (as a child) inside header_button class', () => {
        // Include the AccessButton component in the test as a child of Header
        // Set the isLoggedIn from the parent to false
        const modifiedWrapper = shallowMount(Header, {
            global: {
                components: { AccessButton },
                provide: { isLoggedIn: { value: false } }
            }
        });

        expect(modifiedWrapper.find('.header_button').findComponent(AccessButton).exists()).toBe(true);
    });

    it('emits "accessButtonEvent" event when AccessButton is clicked', () => {
        const wrapper = shallowMount(Header, {
            global: {
                components: { AccessButton },
                provide: { isLoggedIn: { value: false } }
            }
        });
        wrapper.findComponent(AccessButton).vm.$emit('accessButtonEvent');
        expect(wrapper.emitted('accessButtonEvent')).toBeTruthy();
    });
});

/**
 * Note: the current convention is that the header should have only 3 links when
 * the user is not logged in, and 6 links when the user is logged in (inside the 
 * "header_nav_bar" nav class). Furthermore, the text of the AccessButton changes; 
 * however, that is covered in the AccessButton test suite.
 * 
 * Furthermore, this test covers the router-link functionality of the navigation bar.
 * This way, we can test what the user has access to based on the status of the user.
 * 
 * Note: there could be a test that would check whether the links are in the correct order,
 * but we are not concerned with that at the moment. It is significantly more important that
 * all the required links are present.
 */
describe('Check the logic based on the logged in status', () => {
    it('renders navigation links for signed out users properly in the desired format', () => {
        const wrapper = shallowMount(Header, {
            global: {
                provide: { isLoggedIn: { value: false } } // Mock the injected property
            }
        });
        expect(wrapper.find('.header_nav_bar').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar').isVisible()).toBe(true);
        expect(wrapper.findAll('.header_nav_bar a').length).toBe(3); // Make sure there are 3 links
        expect(wrapper.find('.header_nav_bar a[href="#/about"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/help"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/contact"]').exists()).toBe(true);
    });

    it('renders navigation links for signed in users properly in the desired format', () => {
        const wrapper = shallowMount(Header, {
            global: {
                provide: { isLoggedIn: { value: true } } // Mock the injected property
            }
        });
        expect(wrapper.find('.header_nav_bar').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar').isVisible()).toBe(true);
        expect(wrapper.findAll('.header_nav_bar a').length).toBe(6); // Make sure there are 6 links
        expect(wrapper.find('.header_nav_bar a[href="#/"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/about"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/help"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/contact"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/your-terrariums"]').exists()).toBe(true);
        expect(wrapper.find('.header_nav_bar a[href="#/settings"]').exists()).toBe(true);
    });
});
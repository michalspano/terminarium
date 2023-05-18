/***************************************************************************************************
 * Terminarium (test suite)
 * File: {@code AccessButton.spec.js}
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

// Import the test suite functionality
import { shallowMount } from '@vue/test-utils';
import { describe, it, expect } from 'vitest';

// Import the component(s) being tested
import AccessButton from '@/components/AccessButton.vue';

describe('Check that the components are being imported properly', () => {
    it('should import AccessButton', () => {
        expect(AccessButton).toBeDefined();
    });
});

describe('Check that the component is being rendered', () => {
    const wrapper = shallowMount(AccessButton, {
        global: {
            provide: { isLoggedIn: { value: false } }   // the injected value is not used in the test
                                                        // but it is required for the component to be rendered
        }
    });
    it('should exist', () => {
        expect(wrapper.exists()).toBe(true);
    });
});

describe('Check that the structure of the component is correct', () => {
    const wrapper = shallowMount(AccessButton, {
        global: {
            provide: { isLoggedIn: { value: false } }
        }
    });

    it('should contain a button instance with class "access"', () => {
        expect(wrapper.find('button.access').exists()).toBe(true);
    });
});

describe('Check the click functionality of the button', () => {
    const wrapper = shallowMount(AccessButton, {
        global: {
            provide: { isLoggedIn: { value: false } }
        }
    });

    /* Note: when an element is not 'clickable', its property "disabled" is set to true.
     * Hence, we expect that such property is undefined (i.e. not set/false). */
    it('should be clickable', () => {
        expect(wrapper.find('button').attributes('disabled')).toBeUndefined();
    });

    // Check that the button emits the correct event when clicked (i.e. "accessButtonEvent")
    it('should emit "accessButtonEvent" event when clicked', async () => {
        await wrapper.find('button').trigger('click');
        expect(wrapper.emitted('accessButtonEvent')).toBeTruthy();
    });
});

/* Note: the expected string values based on the state could be stored in some structure
*   i.e. an array, a map, etc. However, due to the verbosity of the utility functions
*   provided by the testing framework, we will use the string values directly. This way,
*   the readability of the tests is greatly enhanced, and one can easily see what is
*   being tested. */
describe('Check the logic of the component based on the login stats', () => {
    it('should display "log in" when the user is not logged in', () => {
        const wrapper = shallowMount(AccessButton, {
            global: {
                provide: { isLoggedIn: { value: false } }
            }
        });
        /* Assumption: since the template contains only a single button,
         * we can use the "button" selector to find it. Otherwise, we would
         * have to use the "findComponent" method.*/
        expect(wrapper.find('button').text()).toBe('log in');
    });

    it('should display "log out" when the user is logged in', () => {
        const wrapper = shallowMount(AccessButton, {
            global: {
                provide: { isLoggedIn: { value: true } }
            }
        });
        // Same assumption as above
        expect(wrapper.find('button').text()).toBe('log out');
    });
});

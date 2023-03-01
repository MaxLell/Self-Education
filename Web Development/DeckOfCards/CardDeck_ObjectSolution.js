const cardDeck = {
    deck: [],
    usedCards: [],

    maximumCards: 52,

    suits: ['hearts', 'diamonds', 'spades', 'clubs'],
    values: '2,3,4,5,6,7,8,9,10,J,Q,K,A'.split(','),

    initializeDeck() {
        /**
         * Instead of typing out this.variable for every
         * Variable which is to be used within this function
         * One can use object destructuring to pass the data
         * into simple variables. The names of these variables
         * need to match the properties of the object.
         */
        const { suits, values, deck, usedCards } = this;

        /**
         * Clear the existing decks. There are multiple ways 
         * to do this.
         */
        deck.length = 0;
        while (usedCards.length > 0) {
            usedCards.pop();
        }

        for (s of suits) {
            for (v of values) {
                deck.push({ 'suit': s, 'value': v });
            }
        }
    },
    drawCardFromDeck() {
        const card = this.deck.pop();
        this.usedCards.push(card);
        return card;
    },

    drawMultipleCardsFromDeck(numberOfCardsToDraw) {
        const cardsArray = [];
        for (let i = 0; i < numberOfCardsToDraw; i++) {
            cardsArray.push(this.drawCardFromDeck());
        }
        return cardsArray;
    },
    drawRandomCardFromDeck() {
        const { deck, usedCards } = this;

        // get the random index
        const randomIndex = Math.floor(Math.random() * deck.length);

        // splice out the element from the deck 
        const randomCardInArray = deck.splice(randomIndex, 1);

        // extract the card from the array
        const card = randomCardInArray[0];

        // add the card to the usedCard stack
        usedCards.push(card);

        return card;
    },

    shuffle() {
        /**
         * This function shuffles the remaining cards in the deck
         * This is a brute force algorithm. There are much slimmer
         * solutions like the Fisher-Yates shuffle algorithm. 
         * But this is not the target of this exercise.
         * The complexity of this algorithm to shuffle the deck is 2n
         */
        const { deck } = this;

        const deckSize = deck.length;
        const tmpDeck = [];

        for (let i = 0; i < deckSize; i++) {
            // get the random index from the current ordered array
            const randomIndex = Math.floor(Math.random() * deck.length);

            // splice out the random element from this array
            const randomCardInArray = deck.splice(randomIndex, 1);

            /**
             * Extract the card from the provided array and create
             * a deep copy of it in the temporal array.
             */
            tmpDeck[i] = { ...randomCardInArray[0] };

        }

        /**
         * Overwrite all elements within the current deck
         */
        for (let i = 0; i < deckSize; i++) {
            deck[i] = tmpDeck[i];
        }
    }

}

/**
 * Automated tests
 * Since I am not yet encounter a test framework in JS
 * I will create some automated tests by foot.
 */

/**
 * inializeDeck - test
 * In order to display the before and after of the 
 * card deck, one needs to create a deep copy of the
 * array. The browser runs the script and as the reference
 * remains the same also the before value is updated.
 * Therefore a deep copy with array destructuring needs to 
 * be made to properly see the difference.
 * 
 * A bit of TDD and the usage of ternary operators. This
 * is not the simplest to read, but for practice this is
 * ok.
 * Furthermore since this is only a small exercise, this
 * test set is not complete by all means.
 */
const failMsg = 'FAIL!!!';
const successMsg = 'pass';

let testCounter = 1;
function log_results(result, testDescription) {
    console.log(`Test ${testCounter}`);
    testCounter++;
    if (result === failMsg) {
        console.log(`test did %c${result}`, 'color: #C70039 ');
    }
    else {
        console.log(`test did %c${result}`, 'color:  #27a400 ');
    }
    console.log(`${testDescription}`);
    console.log('------------------------------------------');
}

log_results(
    (([...cardDeck.deck].length === 0) ? successMsg : failMsg),
    'Card Deck should be empty?'
);

cardDeck.initializeDeck();

log_results(
    (([...cardDeck.deck].length === cardDeck.maximumCards) ? successMsg : failMsg),
    'Card Deck should be populated'
);



/**
 * drawCardFromDeck() - test
 * The pop operation within this function removes one element
 * from the deck. 
 */
// Do a fresh start
cardDeck.initializeDeck();

// set the expected value
const expectedDeckSizeAfter = cardDeck.maximumCards - 1;

// Run the FUT
cardDeck.drawCardFromDeck();

// Run the check
let result = (cardDeck.deck.length === expectedDeckSizeAfter) ? successMsg : failMsg;

// Log the result
log_results(
    result,
    'drawCardFromDeck() reduced size by one?'
);


/**
 * usedCard Deck updated?
 */

// Do a fresh start
cardDeck.initializeDeck();

// get the current length of the usedCards array
const beforeLength = cardDeck.usedCards.length;

// run the drawCard function, to get one card.
const card = cardDeck.drawCardFromDeck();

// This also adds an element to the usedCards array
const afterLength = cardDeck.usedCards.length;

// Run the test
result = (beforeLength + 1 === afterLength) ? successMsg : failMsg;

// Log the result
log_results(
    result,
    'usedCard deck is updated after card is drawn'
);

/**
 * Can multiple cards be obtained?
 */

// Do a fresh start
cardDeck.initializeDeck();

const cardsToDraw = 5;
const cardsArray = cardDeck.drawMultipleCardsFromDeck(cardsToDraw);

result = (cardsArray.length === cardsToDraw) ? successMsg : failMsg;
log_results(
    result,
    'drawMultipleCardsFromDeck should return 5 cards, upon a request of 5 cards'
);

/**
 * Can a random card be drawn?
 */

/** Reset the object */
cardDeck.initializeDeck();

const drawnRandomCards = [];
const failStatus = -1;

for (let i = 0; i < cardDeck.maximumCards; i++) {
    // Get a random card
    const randomCard = cardDeck.drawRandomCardFromDeck();

    /**
     * check whether there is already an element like it on this stack
     */
    if (failStatus !== drawnRandomCards.indexOf(randomCard)) {

        /**
         * If only one is already there, the algorithm is
         * not working 
         */
        result = failMsg;
        break;
    }
    else { // randomCard is not present in the already drawn cards
        /**
         * Push the card onto the drawn stack
         */
        drawnRandomCards.push(randomCard);
        result = successMsg;
    }

}
log_results(
    result,
    'the card that is drawn has not been seen before'
)

/**
 * Shuffle Deck functionality
 */

/** Reset the object */
cardDeck.initializeDeck();

const beforeDeck = [...cardDeck.deck];

cardDeck.shuffle();

const afterDeck = [...cardDeck.deck];

/**
 * Compare the decks - they should be different at at least 10 positions
 * This test has the worst time complexity ever ... 
 * The probability that this is not working is very very low.
 * But these are only 52 cards at max, therefore the garbage will do.
 */
let counter = 0;
for (let i = 0; i < cardDeck.maximumCards; i++) {
    if (beforeDeck[i].suit !== afterDeck[i].suit) {
        if (beforeDeck[i].value !== afterDeck[i].value) {
            counter++;
        }
    }
}

result = (counter >= 10) ? successMsg : failMsg;
log_results(
    result,
    `shuffleDeck shall create a shuffled deck, that is
    different from the original deck in at least 10 
    positions`
);

/**
 * The start of a regular poker game
 */

cardDeck.initializeDeck();
cardDeck.shuffle();
const givenHands = [];
const players = 6;

console.log(`Poker Game scenario with ${players} players`);
console.log('------------------------------------------');

for (let i = 0; i < players; i++) {
    console.log(`Player ${i + 1} cards:`)
    const hand = cardDeck.drawMultipleCardsFromDeck(2);
    console.log(`${hand[0].value} - ${hand[0].suit} | ${hand[1].value} - ${hand[1].suit}`);

    console.log('.............................');
}










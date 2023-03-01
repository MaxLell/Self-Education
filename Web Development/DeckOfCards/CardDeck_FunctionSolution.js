/* Possible Feature Set */
// pull a single card of the deck
// have a discard pile of cards, that were already played
// shuffle functionality - to shuffle the deck
// Refill the deck, start over from scratch
// draw(5), draw(2) - gets 5 or 2 cards from the deck
// put cards on the discard pile

/**
 * Create every possible combination
 * {value: '5', suit: 'hearts'} and
 * return the entire deck as an array 
 * of these objects
 */
function makeDeck() {
    const suits = ['hearts', 'diamonds', 'spades', 'clubs'];
    let values = '2,3,4,5,6,7,8,9,10,J,Q,K,A';
    values = values.split(',');

    const deck = [];

    let idx = 0;
    for (s of suits) {
        for (v of values) {
            /**
             * It is crucially important that current card
             * is only defined and created in the for loop.
             * The push operation does not seem to pass a
             * deep copy of the object. But rather then that 
             * it only passes the reference.
             * 
             * There are other options also, which are commented
             * out below
             */
            const currentCard = {};
            currentCard.suit = s;
            currentCard.value = v;

            /**
             * This operation would allow the currentCard
             * object to be defined outside. The spread
             * operation creates such a deep copy of the 
             * object.
             */
            //deck.push({ ...currentCard });

            /**
             * This would also work. It creates a completly
             * new object in each iteration. The reference of 
             * each of these completly new objects are pushed
             * into the array.
             */
            // deck.push({ 'suit': s, 'value': v });

            deck.push(currentCard);
        }
    }
    return deck;
}

/**
 * Create a function that draws a random card from the deck.
 * The current function does return a deep copy of the current
 * card. Therefore the card which is put out can be modified
 * outside, without affecting the original card in the deck
 */
function drawRandomCardFrom(deck) {
    const randomIdx = Math.floor(Math.random() * deck.length);
    return { ...deck[randomIdx] };
}
console.log(drawRandomCardFrom(makeDeck()));

/**
 * This is a very simple function, using the builtin array function
 * One needs to notice, that this alters the original array. Under
 * the hood really is a linked list, from which one can pop elements
 * of. 
 */
const drawCard = (deck) => {
    return deck.pop();
}

/**
 * This is a procedure that goes out of bounds of the existing array.
 * This is an experiment to see what happens when things go out of bounds
 * The max size of the current deck is 52, therefore at the 53rd attempt
 * the array will run out of bounds and its value is 'undefined'
 */
const deck = makeDeck()
for (let i = 0; i < 100; i++) {
    let card = drawCard(deck);
    console.log(`Current Deck Size: ${deck.length}`, card);
}

/**
 * In order to access the deck one would need to create a global variable
 * which is then to be passed around. This is also the way how it is done in C
 * Therefore a novel approach is to be taken and to implement all the 
 * functionality within an object.
 * This functionality will be created in a seperate script
 * Checkout the CardDeck_ObjectSolution.js script
 */
const { RNG } = require('./build/Release/rng');
const { performance } = require('perf_hooks'); 

const RTP = 0.97;
const MAX_MULTIPLIER = 1000_000; 
const NUM_ROUNDS = 1000_000_00; 
const hits = new Array(MAX_MULTIPLIER + 1).fill(0); 

const rng = new RNG(RTP, MAX_MULTIPLIER);

const startTime = performance.now(); 

for(let i=0; i<NUM_ROUNDS; i++){
    const multi = rng.getMultiplier(); 
    hits[multi]++; 
}

const endTime = performance.now(); 
console.log('Time Taken: ', (endTime - startTime)/1000, 's'); 

for(let i=100; i<=MAX_MULTIPLIER; i++){
    if(hits[i] === 0) console.log(i/100);
    if(i >= 300) break; 
}

console.log('1x: ', hits[100], '\n10000x:', hits[MAX_MULTIPLIER]); 

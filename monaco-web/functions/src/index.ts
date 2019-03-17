import * as functions from 'firebase-functions';
import * as admin from 'firebase-admin';

admin.initializeApp();

const db = admin.firestore();

export const driveRequest = functions.https.onRequest((request, response) => {
    db.collection('driving_requests').doc('current').get()
        .then(doc => {
            if (!doc.exists) {
                console.error('Document not found!');
            } else {
                const docData: any = doc.data();
                console.log('Document data:', docData);

                const arrayBuffer = new ArrayBuffer(8);
                const buffer = Buffer.from(arrayBuffer);
                const view = new Float32Array(arrayBuffer);

                view[0] = docData.steering;
                view[1] = docData.powertrain;

                console.log('Array buffer:', arrayBuffer);
                console.log('Buffer:', buffer);
                console.log('View:', view);

                response.contentType('application/octet-stream');
                response.send(buffer);
            }
        })
        .catch(err => {
            console.error('Error getting document', err);
        });
});

export const displacement = functions.https.onRequest((request, response) => {
    db.collection('displacement').doc('current').get()
        .then(doc => {
            if (!doc.exists) {
                console.error('Document not found!');
            } else {
                const docData: any = doc.data();
                console.log('Document data:', docData);

                const arrayBuffer = new ArrayBuffer(8);
                const buffer = Buffer.from(arrayBuffer);
                const view = new Float32Array(arrayBuffer);

                view[0] = docData.x;
                view[1] = docData.y;

                console.log('Array buffer:', arrayBuffer);
                console.log('Buffer:', buffer);
                console.log('View:', view);

                response.contentType('application/octet-stream');
                response.send(buffer);
            }
        })
        .catch(err => {
            console.error('Error getting document', err);
        });
});

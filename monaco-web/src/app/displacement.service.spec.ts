import { TestBed } from '@angular/core/testing';

import { DisplacementService } from './displacement.service';

describe('DisplacementService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: DisplacementService = TestBed.get(DisplacementService);
    expect(service).toBeTruthy();
  });
});
